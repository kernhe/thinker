
#include "move.h"

constexpr int IMP_SIMPLE = (TERRA_FARM | TERRA_MINE | TERRA_FOREST);
constexpr int IMP_ADVANCED = (TERRA_CONDENSER | TERRA_THERMAL_BORE);
constexpr int PM_SAFE = -20;
constexpr int PM_NEAR_SAFE = -40;

/*

Priority Map Tables contain values calculated for each map square
to guide the AI in its move planning.

The tables contain only ephemeral values: they are recalculated each turn
for every active faction, and the values are never saved with the save games.

For example, pm_former counter is decremented whenever a former starts
work on a given square to prevent too many of them converging on the same spot.
It is also used as a shortcut to determine if a square has a friendly base
in a 2-tile radius, because formers are only allowed to work on squares which
are reachable by a friendly base worker.

Non-combat units controlled by Thinker (formers, colony pods, land-based crawlers)
use pm_safety table to decide if there are enemy units too close to them.
PM_SAFE defines the threshold below which the units will attempt to flee
to the square chosen by escape_move.

*/
PMTable pm_former;
PMTable pm_safety;
PMTable pm_roads;
PMTable pm_enemy;
PMTable pm_enemy_near;
PMTable pm_overlay;

bool build_tubes = false;
int need_ferry = 0;
int last_faction = 0;

void adjust_value(PMTable tbl, int x, int y, int range, int value) {
    for (const MapTile& m : iterate_tiles(x, y, 0, TableRange[range])) {
        tbl[m.x][m.y] += value;
    }
}

bool other_in_tile(int faction, MAP* sq) {
    int u = unit_in_tile(sq);
    return (u >= 0 && u != faction);
}

bool non_ally_in_tile(int faction, MAP* sq) {
    int u = unit_in_tile(sq);
    return u >= 0 && u != faction && !has_pact(faction, u);
}

HOOK_API int mod_enemy_move(int id) {
    assert(id >= 0 && id < MaxVehNum);
    VEH* veh = &tx_vehicles[id];
    int faction = veh->faction_id;
    if (ai_enabled(faction)) {
        int w = veh->weapon_type();
        if (w == WPN_COLONY_MODULE) {
            return colony_move(id);
        } else if (w == WPN_SUPPLY_TRANSPORT) {
            return crawler_move(id);
        } else if (w == WPN_TERRAFORMING_UNIT) {
            return former_move(id);
        } else if (w == WPN_TROOP_TRANSPORT && veh_triad(id) == TRIAD_SEA) {
            return trans_move(id);
        } else if (w <= WPN_PSI_ATTACK && veh_triad(id) != TRIAD_AIR) {
            return combat_move(id);
        }
    }
    return enemy_move(id);
}

HOOK_API int log_veh_kill(int UNUSED(ptr), int id, int UNUSED(owner), int UNUSED(unit_id)) {
    /* This logging function is called whenever a vehicle is removed/killed for any reason. */
    VEH* veh = &tx_vehicles[id];
    if (ai_enabled(*active_faction) && at_war(*active_faction, veh->faction_id)) {
        if (veh->x >= 0 && veh->y >= 0) {
            adjust_value(pm_enemy_near, veh->x, veh->y, 3, -1);
            pm_enemy[veh->x][veh->y]--;
        }
    }
    return 0;
}

void adjust_route(PMTable tbl, const TileSearch& ts, int value) {
    int i = 0;
    int j = ts.cur;
    while (j >= 0 && ++i < PathLimit) {
        auto p = ts.newtiles[j];
        j = p.prev;
        tbl[p.x][p.y] += value;
    }
}

int route_distance(PMTable tbl, int x1, int y1, int x2, int y2) {
    Points visited;
    std::list<PathNode> items;
    items.push_back({x1, y1, 0, 0});
    int limit = max(8, map_range(x1, y1, x2, y2) * 2);
    int i = 0;

    while (items.size() > 0 && ++i < 120) {
        PathNode cur = items.front();
        items.pop_front();
        if (cur.x == x2 && cur.y == y2 && cur.dist <= limit) {
            debug("route_distance %d %d -> %d %d = %d %d\n", x1, y1, x2, y2, i, cur.dist);
            return cur.dist;
        }
        for (const int* t : NearbyTiles) {
            int rx = wrap(cur.x + t[0]);
            int ry = cur.y + t[1];
            if (mapsq(rx, ry) && tbl[rx][ry] > 0 && !visited.count({rx, ry})) {
                items.push_back({rx, ry, cur.dist + 1, 0});
                visited.insert({rx, ry});
            }
        }
    }
    return -1;
}

/*
Evaluate possible land bridge routes from home continent to other regions.
Planned routes are stored in the faction goal struct and persist in save games.
*/
void land_raise_plan(int faction, bool visual) {
    int tile_count[MaxRegionNum] = {};
    int base_count[MaxRegionNum] = {};
    PMTable pm_shore = {};
    AIPlans& p = plans[faction];

    if (p.main_region < 0) {
        return;
    }   
    for (int y = 0; y < *map_axis_y; y++) {
        for (int x = y&1; x < *map_axis_x; x+=2) {
            MAP* sq = mapsq(x, y);
            if (sq && sq->region < MaxRegionNum) {
                tile_count[sq->region]++;
                if (sq->items & TERRA_BASE_IN_TILE) {
                    base_count[sq->region]++;
                }
                if (is_ocean(sq)) {
                    adjust_value(pm_shore, x, y, 1, 1);
                }
                // Note linear tile iteration order
                assert(pm_shore[x][y] <= 6);
            }
        }
    }
    int best_score = 10;
    int goal_count = 0;
    int land = 0;
    int bases = 0;
    PointList path;
    Points mainland;
    TileSearch ts;
    MAP* sq;
    MAP* bsq;

    ts.init(p.main_region_x, p.main_region_y, TS_TERRITORY_LAND, 4);
    while (++land < 500 && (sq = ts.get_next()) != NULL) {
        assert(!is_ocean(sq));
        if (sq->items & TERRA_BASE_IN_TILE) {
            bases++;
        } else {
            mainland.insert({ts.rx, ts.ry});
        }
    }
    debug("raise_plan %d land: %d bases: %d region_land: %d region_bases: %d\n",
        faction, land, bases, tile_count[p.main_region], base_count[p.main_region]);

    for (auto pt : mainland) {
        int x = pt.x;
        int y = pt.y;
        int i = 0;
        bsq = mapsq(x, y);
        if (pm_shore[x][y] < 3 || !bsq || bsq->items & TERRA_BASE_IN_TILE) {
            continue;
        }
        ts.init(x, y, TS_SEA_AND_SHORE, 4);

        while (++i < 500 && (sq = ts.get_next()) != NULL && ts.dist <= 12) {
            if (!(sq->region != p.main_region && sq->region > 0 && sq->region < 63)) {
                continue;
            }
            int score = min(100, tile_count[sq->region]) - ts.dist*ts.dist/2
                + (bsq->items & TERRA_BASE_RADIUS ? 20 : 0);

            // Check if we should bridge to hostile territory
            if (sq->owner != faction && sq->owner > 0 && !has_pact(faction, sq->owner)) {
                int w1 = faction_might(faction);
                int w2 = faction_might(sq->owner);
                score += 80*(w1-w2)/w1 + min(0, pm_safety[ts.rx][ts.ry] / 4);
            }
            if (score > best_score) {
                best_score = score;
                debug("raise_goal %2d %2d -> %2d %2d dist: %2d size: %3d owner: %d score: %d\n",
                    x, y, ts.rx, ts.ry, ts.dist, tile_count[sq->region], sq->owner, score);

                for (auto pp : ts.get_route(path)) {
                    if (visual) {
                        pm_overlay[pp.x][pp.y] = score;
                    } else {
                        add_goal(faction, AI_GOAL_RAISE_LAND, 5, pp.x, pp.y, -1);
                    }
                    goal_count++;
                }
            }
            if (goal_count > 15) {
                return;
            }
        }
        adjust_value(pm_shore, x, y, 1, -10); // Skip adjacent tiles
    }
}

void invasion_plan(int faction1, int faction2) {
    const int ShoreLine = 256;
    int sea_region = 0;
    int tile_count[MaxRegionNum] = {};
    MAP* sq;
    PMTable pm_shore = {};
    AIPlans& p1 = plans[faction1];
    AIPlans& p2 = plans[faction2];

    if (p1.main_region < 0 || p2.main_region < 0 || p1.main_region == p2.main_region) {
        return;
    }   
    for (int y = 0; y < *map_axis_y; y++) {
        for (int x = y&1; x < *map_axis_x; x+=2) {
            sq = mapsq(x, y);
            if (sq && sq->region < MaxRegionNum) {
                tile_count[sq->region]++;
                if (is_ocean(sq)) {
                    adjust_value(pm_shore, x, y, 1, 1);
                    if (tile_count[sq->region] > tile_count[sea_region]) {
                        sea_region = sq->region;
                    }
                }
                assert(pm_shore[x][y] <= 6);
            }
        }
    }
    p1.main_sea_region = sea_region;
    for (int y = 0; y < *map_axis_y; y++) {
        for (int x = y&1; x < *map_axis_x; x+=2) {
            sq = mapsq(x, y);
            if (sq && sq->region == sea_region) {
                adjust_value(pm_shore, x, y, 1, ShoreLine);
            }
        }
    }
    TileSearch ts;
    int min_dist = INT_MAX;
    int start_x = -1;
    int start_y = -1;
    
    for (int i=0; i < *total_num_bases; i++) {
        BASE* base = &tx_bases[i];
        if (base->faction_id == faction1 && pm_shore[base->x][base->y] >= ShoreLine
        && !is_ocean(base)) {
            int dist = map_range(base->x, base->y, p2.main_region_x, p2.main_region_y);
            if (dist < min_dist) {
                min_dist = dist;
                start_x = base->x;
                start_y = base->y;
            }
        }
    }
    int i = 0;
    ts.init(start_x, start_y, TS_SEA_AND_SHORE, 0);
    while (++i < 1200 && (sq = ts.get_next()) != NULL) {
        if (pm_shore[ts.rx][ts.ry] >= ShoreLine
        && sq->region == p2.main_region
        && ~sq->items & TERRA_BASE_IN_TILE
        && !non_ally_in_tile(faction1, sq)) {

            PathNode& prev = ts.newtiles[ts.newtiles[ts.cur].prev];
            bool current_goal = has_goal(faction1, AI_GOAL_NAVAL_BEACH, ts.rx, ts.ry)
                || has_goal(faction1, AI_GOAL_NAVAL_END, prev.x, prev.y);

            int score = min(40, pm_safety[ts.rx][ts.ry] / 4)
                + (sq->items & (TERRA_ROAD | TERRA_RIVER) ? 40 : 0)
                + (sq->items & (TERRA_BASE_RADIUS) ? 35 : 0)
                + (sq->items & (TERRA_FUNGUS) && plans[faction1].keep_fungus ? 30 : 0)
                + (sq->items & (TERRA_FOREST) ? 30 : 0)
                + (current_goal ? 120 : 0)
                - 9*ts.dist;

            if (score > p1.naval_score) {
                p1.naval_score = score;
                p1.naval_start_x = start_x;
                p1.naval_start_y = start_y;
                p1.naval_beach_x = ts.rx;
                p1.naval_beach_y = ts.ry;
                p1.naval_end_x = prev.x;
                p1.naval_end_y = prev.y;

                debug("invasion %d -> %d start: %2d %2d end: %2d %2d dist: %2d score: %d\n",
                    faction1, faction2, start_x, start_y, ts.rx, ts.ry, ts.dist, score);
            }
        }
    }
}

void update_main_region(int faction) {
    for (int i=1; i < MaxPlayerNum; i++) {
        AIPlans& p = plans[i];
        p.main_region = -1;
        p.main_region_x = -1;
        p.main_region_y = -1;
        if (i == faction) {
            p.aircraft = 0;
            p.transports = 0;
            p.prioritize_naval = 0;
            p.main_sea_region = -1;
            p.naval_score = -1000;
            p.naval_start_x = -1;
            p.naval_start_y = -1;
            p.naval_end_x = -1;
            p.naval_end_y = -1;
            p.naval_beach_x = -1;
            p.naval_beach_y = -1;
        }
    }

    for (int i=0; i < *total_num_bases; i++) {
        BASE* base = &tx_bases[i];
        MAP* sq = mapsq(base->x, base->y);
        AIPlans& p = plans[base->faction_id];
        if (p.main_region < 0 && !is_ocean(sq)) {
            p.main_region = sq->region;
            p.main_region_x = base->x;
            p.main_region_y = base->y;
        }
    }
    // Prioritize naval invasions if the closest enemy is on another region
    AIPlans& p = plans[faction];
    int min_dist = INT_MAX;
    for (int i=1; i < MaxPlayerNum; i++) {
        int dist = map_range(p.main_region_x, p.main_region_y,
            plans[i].main_region_x, plans[i].main_region_y);
        if (at_war(faction, i) && dist < min_dist) {
            min_dist = dist;
            p.prioritize_naval = p.main_region != plans[i].main_region;
        }
    }
}

void move_upkeep(int faction, bool visual) {
    Faction& f = tx_factions[faction];
    AIPlans& p = plans[faction];
    if (!ai_enabled(faction)) {
        return;
    }
    last_faction = faction;
    need_ferry = 0;
    mapnodes.clear();
    memset(pm_former, 0, sizeof(pm_former));
    memset(pm_safety, 0, sizeof(pm_safety));
    memset(pm_roads, 0, sizeof(pm_roads));
    memset(pm_enemy, 0, sizeof(pm_enemy));
    memset(pm_enemy_near, 0, sizeof(pm_enemy_near));
    build_tubes = has_terra(faction, FORMER_MAGTUBE, 0);
    update_main_region(faction);
    debug("main_region %d %2d x: %2d y: %2d naval: %d\n",
        faction, p.main_region, p.main_region_x, p.main_region_y, p.prioritize_naval);

    MAP* sq;
    for (int y=0; y < *map_axis_y; y++) {
        for (int x=y&1; x < *map_axis_x; x += 2) {
            if (!(sq = mapsq(x, y))) {
                continue;
            }
            if (sq->owner == faction && ((!build_tubes && sq->items & TERRA_ROAD)
            || (build_tubes && sq->items & TERRA_MAGTUBE))) {
                pm_roads[x][y]++;
            } else if (unit_in_tile(sq) < 0 && goody_at(x, y)) {
                mapnodes.insert({x, y, NODE_PATROL});
            }
        }
    }
    for (int i=0; i < *total_num_vehicles; i++) {
        VEH* veh = &tx_vehicles[i];
        UNIT* u = &tx_units[veh->proto_id];

        if (veh->move_status == ORDER_THERMAL_BOREHOLE) {
            mapnodes.insert({veh->x, veh->y, NODE_BOREHOLE});
        }
        if (veh->faction_id == faction) {
            int triad = veh_triad(i);
            if (u->weapon_type <= WPN_PSI_ATTACK) {
                adjust_value(pm_safety, veh->x, veh->y, 1, 40);
                pm_safety[veh->x][veh->y] += 60;
                if (triad == TRIAD_AIR) {
                    p.aircraft++;
                }
            }
            if (triad == TRIAD_LAND && !is_ocean(mapsq(veh->x, veh->y))) {
                veh->state &= ~VSTATE_IN_TRANSPORT;
            }
            if ((u->weapon_type == WPN_COLONY_MODULE || u->weapon_type == WPN_TERRAFORMING_UNIT)
            && triad == TRIAD_LAND) {
                sq = mapsq(veh->x, veh->y);
                if (sq && is_ocean(sq) && sq->items & TERRA_BASE_IN_TILE
                && coast_tiles(veh->x, veh->y) < 8) {
                    mapnodes.insert({veh->x, veh->y, NODE_NEED_FERRY});
                    need_ferry++;
                }
            }
            if (u->weapon_type == WPN_TROOP_TRANSPORT && triad == TRIAD_SEA) {
                p.transports++;
            }
            if (veh->waypoint_1_x >= 0) {
                mapnodes.erase({veh->waypoint_1_x, veh->waypoint_1_y, NODE_PATROL});
            }
        } else if (at_war(faction, veh->faction_id)) {
            int val = (u->weapon_type <= WPN_PSI_ATTACK && veh->proto_id != BSC_FUNGAL_TOWER ? -100 : -10);
            adjust_value(pm_safety, veh->x, veh->y, 1, val);
            if (val == -100) {
                int w = (u->chassis_type == CHS_INFANTRY ? 2 : 1);
                adjust_value(pm_safety, veh->x, veh->y, 4-w, val/(w*4));
            }
            adjust_value(pm_enemy_near, veh->x, veh->y, 3, 1);
            pm_enemy[veh->x][veh->y]++;
        }
    }
    TileSearch ts;
    for (int i=0; i < *total_num_bases; i++) {
        BASE* base = &tx_bases[i];
        if (base->faction_id == faction) {
            adjust_value(pm_former, base->x, base->y, 2, base->pop_size);
            pm_safety[base->x][base->y] += 10000;

            if (!is_ocean(base)) {
                int j = 0;
                int k = 0;
                ts.init(base->x, base->y, TS_TERRITORY_LAND);
                while (++j < 150 && k < 5 && (sq = ts.get_next()) != NULL) {
                    if (sq->items & TERRA_BASE_IN_TILE) {
                        if (route_distance(pm_roads, base->x, base->y, ts.rx, ts.ry) < 0) {
                            debug("route_add %d %d -> %d %d\n", base->x, base->y, ts.rx, ts.ry);
                            adjust_route(pm_roads, ts, 1);
                        }
                        k++;
                    }
                }
            }
        }
    }
    if (visual) {
        memcpy(pm_overlay, pm_safety, sizeof(pm_safety));
        return;
    }

    if (has_terra(faction, FORMER_RAISE_LAND, 0) && f.energy_credits > 100 && !(*current_turn % 3)) {
        land_raise_plan(faction, false);
    }
    if (has_chassis(faction, CHS_FOIL)) {
        for (int i=1; i < MaxPlayerNum; i++) {
            if (at_war(faction, i) && tx_factions[i].current_num_bases) {
                invasion_plan(faction, i);
            }
        }
        if (p.naval_end_x >= 0) {
            add_goal(faction, AI_GOAL_NAVAL_START, 3, p.naval_start_x, p.naval_start_y, -1);
            add_goal(faction, AI_GOAL_NAVAL_BEACH, 3, p.naval_beach_x, p.naval_beach_y, -1);
            add_goal(faction, AI_GOAL_NAVAL_END, 3, p.naval_end_x, p.naval_end_y, -1);
        }
    }
    for (int i=0; i<MaxGoalsNum; i++) {
        Goal& goal = f.goals[i];
        if (goal.priority <= 0)
            continue;
        if (goal.type == AI_GOAL_RAISE_LAND)
            mapnodes.insert({goal.x, goal.y, NODE_GOAL_RAISE_LAND});
        if (goal.type == AI_GOAL_NAVAL_START)
            mapnodes.insert({goal.x, goal.y, NODE_GOAL_NAVAL_START});
        if (goal.type == AI_GOAL_NAVAL_BEACH)
            mapnodes.insert({goal.x, goal.y, NODE_GOAL_NAVAL_BEACH});
        if (goal.type == AI_GOAL_NAVAL_END)
            mapnodes.insert({goal.x, goal.y, NODE_GOAL_NAVAL_END});
    }
}

bool need_formers(int x, int y, int faction) {
    assert(faction > 0 && faction < 8);
    MAP* sq;
    int k = 0;
    for (int i=1; i<=20; i++) {
        int x2 = wrap(x + TableOffsetX[i]);
        int y2 = y + TableOffsetY[i];
        sq = mapsq(x2, y2);
        if (sq && sq->owner == faction && select_item(x2, y2, faction, sq) != -1 && ++k > 3) {
            return true;
        }
    }
    return false;
}

bool has_transport(int x, int y, int faction) {
    assert(faction > 0 && faction < 8);
    for (int i=0; i<*total_num_vehicles; i++) {
        VEH* veh = &tx_vehicles[i];
        if (veh->faction_id == faction && veh->x == x && veh->y == y
        && veh->weapon_type() == WPN_TROOP_TRANSPORT) {
            return true;
        }
    }
    return false;
}

bool non_combat_move(int x, int y, int faction, int triad) {
    MAP* sq = mapsq(x, y);
    if (!sq || (sq->owner > 0 && sq->owner != faction)) {
        return false;
    }
    if (triad != TRIAD_AIR && !sq->is_base() && is_ocean(sq) != (triad == TRIAD_SEA)) {
        return false;
    }
    if (!non_ally_in_tile(faction, sq)) {
        return last_faction != faction || pm_safety[x][y] >= PM_NEAR_SAFE;
    }
    return false;
}

void count_bases(int x, int y, int faction, int triad, int* area, int* bases) {
    assert(triad == TRIAD_LAND || triad == TRIAD_SEA || triad == TRIAD_AIR);
    MAP* sq;
    *area = 0;
    *bases = 0;
    int i = 0;
    TileSearch ts;
    ts.init(x, y, triad, 2);
    while (++i < 200 && (sq = ts.get_next()) != NULL) {
        if (sq->items & TERRA_BASE_IN_TILE) {
            (*bases)++;
        } else if (can_build_base(ts.rx, ts.ry, faction, triad)) {
            (*area)++;
        }
    }
    debug("count_bases %2d %2d triad: %d area: %d bases: %d\n", x, y, triad, *area, *bases);
}

bool has_base_sites(int x, int y, int faction, int triad) {
    int area;
    int bases;
    count_bases(x, y, faction, triad, &area, &bases);
    return area > bases+4;
}

bool need_heals(VEH* veh) {
    return veh->damage_taken > 2 && veh->proto_id != BSC_BATTLE_OGRE_MK1
        && veh->proto_id != BSC_BATTLE_OGRE_MK2 && veh->proto_id != BSC_BATTLE_OGRE_MK3;
}

bool defend_tile(VEH* veh, MAP* sq) {
    UNIT* u = &tx_units[veh->proto_id];
    if (!sq) {
        return true;
    } else if (need_heals(veh) && sq->items & (TERRA_BASE_IN_TILE | TERRA_MONOLITH)) {
        return true;
    } else if (~sq->items & TERRA_BASE_IN_TILE || u->weapon_type <= WPN_PSI_ATTACK) {
        return false;
    }
    int n = 0;
    for (const int* t : NearbyTiles) {
        int x2 = wrap(veh->x + t[0]);
        int y2 = veh->y + t[1];
        if (mapsq(x2, y2) && pm_safety[x2][y2] < PM_SAFE) {
            n++;
        }
    }
    return n > 3;
}

int escape_score(int x, int y, int range, VEH* veh, MAP* sq) {
    return pm_safety[x][y] - range*120
        + (sq->items & TERRA_MONOLITH && need_heals(veh) ? 1000 : 0)
        + (sq->items & TERRA_BUNKER ? 500 : 0)
        + (sq->items & TERRA_FOREST ? 100 : 0)
        + (sq->rocks & TILE_ROCKY ? 100 : 0);
}

int escape_move(int id) {
    VEH* veh = &tx_vehicles[id];
    MAP* sq = mapsq(veh->x, veh->y);
    if (defend_tile(veh, sq))
        return mod_veh_skip(id);
    int faction = veh->faction_id;
    int tscore = pm_safety[veh->x][veh->y];
    int i = 0;
    int tx = -1;
    int ty = -1;
    TileSearch ts;
    ts.init(veh->x, veh->y, veh_triad(id));
    while (++i < 120 && (sq = ts.get_next()) != NULL) {
        int score = escape_score(ts.rx, ts.ry, ts.dist-1, veh, sq);
        if (score > tscore && !non_ally_in_tile(faction, sq) && !ts.has_zoc(faction)) {
            tx = ts.rx;
            ty = ts.ry;
            tscore = score;
            debug("escape_score %d %d -> %d %d | %d %d %d\n",
                veh->x, veh->y, ts.rx, ts.ry, i, ts.dist, score);
        }
        if (i >= 25 && tscore > 500) {
            break;
        }
    }
    if (tx >= 0) {
        debug("escape_move  %d %d -> %d %d | %d %d\n",
            veh->x, veh->y, tx, ty, pm_safety[veh->x][veh->y], tscore);
        return set_move_to(id, tx, ty);
    }
    if (veh->weapon_type() <= WPN_PSI_ATTACK) {
        return enemy_move(id);
    }
    return mod_veh_skip(id);
}

int trans_move(int id) {
    VEH* veh = &tx_vehicles[id];
    MAP* sq = mapsq(veh->x, veh->y);
    AIPlans& p = plans[veh->faction_id];

    if (!sq || mapnodes.erase({veh->x, veh->y, NODE_NEED_FERRY}) > 0
    || (sq->is_base() && need_heals(veh))) {
        return mod_veh_skip(id);
    }
    int cargo = 0;
    int defenders = 0;
    int capacity = cargo_capacity(id);

    for (int k=0; k < *total_num_vehicles; k++) {
        VEH* v = &tx_vehicles[k];
        if (veh->x == v->x && veh->y == v->y && k != id && veh_triad(k) == TRIAD_LAND) {
            if (v->move_status == ORDER_SENTRY_BOARD && v->waypoint_1_x == id) {
                cargo++;
            } else if (v->is_combat_unit()) {
                defenders++;
            }
        }
    }
    if (is_ocean(sq) && cargo > 0) {
        int x2 = -1;
        int y2 = -1;
        for (MapTile& m : iterate_tiles(veh->x, veh->y, 1, 9)) {
            if (is_ocean(m.sq)) {
                continue;
            }
            if (has_goal(veh->faction_id, AI_GOAL_NAVAL_BEACH, m.x, m.y)) {
                x2 = m.x;
                y2 = m.y;
                break;
            }
            if (p.naval_end_x < 0 && m.sq->owner < 1) {
                x2 = m.x;
                y2 = m.y;
            }
        }
        if (x2 >= 0) {
            for (int k=0; k < *total_num_vehicles; k++) {
                VEH* v = &tx_vehicles[k];
                if (veh->x == v->x && veh->y == v->y && k != id && veh_triad(k) == TRIAD_LAND) {
                    set_move_to(k, x2, y2);
                }
            }
            return SYNC;
        }
    }
    debug("trans_move %d x: %2d y: %2d defenders: %d cargo: %d capacity: %d\n",
          veh->faction_id, veh->x, veh->y, defenders, cargo, cargo_capacity(id));

    if (mapnodes.count({veh->x, veh->y, NODE_GOAL_NAVAL_START})) {
        for (int k=0; k < *total_num_vehicles; k++) {
            if (defenders < 2 || cargo >= capacity) {
                break;
            }
            VEH* v = &tx_vehicles[k];
            if (veh->faction_id == v->faction_id
            && veh->x == v->x && veh->y == v->y && v->is_combat_unit()
            && veh_triad(k) == TRIAD_LAND && v->move_status != ORDER_SENTRY_BOARD) {
                v->move_status = ORDER_SENTRY_BOARD;
                v->waypoint_1_x = id;
                v->waypoint_1_y = 0;
                v->state |= VSTATE_IN_TRANSPORT;
                defenders--;
                cargo++;
            }
        }
        if (cargo >= capacity) {
            return set_move_to(id, p.naval_end_x, p.naval_end_y);
        } else if ((*current_turn + id) % 8 > 0) {
            return mod_veh_skip(id);
        }
    }
    if (cargo > 0 && p.naval_end_x >= 0 && sq->region == p.main_sea_region) {
        debug("trans_move_a %2d %2d -> %2d %2d\n", veh->x, veh->y, p.naval_end_x, p.naval_end_y);
        return set_move_to(id, p.naval_end_x, p.naval_end_y);
    }
    if (!at_target(veh)) {
        return SYNC;
    }
    int i = 0;
    int tx = -1;
    int ty = -1;

    // Naval stackup points are located only on shore bases
    TileSearch ts;
    ts.init(veh->x, veh->y, TS_SEA_AND_SHORE);

    while (++i < 160 && (sq = ts.get_next()) != NULL) {
        if (non_combat_move(ts.rx, ts.ry, veh->faction_id, TRIAD_SEA)) {
            bool to_base = sq->is_base() && sq->owner == veh->faction_id;

            if (mapnodes.count({ts.rx, ts.ry, NODE_GOAL_NAVAL_START})
            || mapnodes.erase({ts.rx, ts.ry, NODE_PATROL})
            || mapnodes.erase({ts.rx, ts.ry, NODE_NEED_FERRY}) > 0
            || (to_base && need_heals(veh))) {
                debug("trans_move_b %2d %2d -> %2d %2d\n", veh->x, veh->y, ts.rx, ts.ry);
                return set_move_to(id, ts.rx, ts.ry);

            } else if (tx < 0 && p.naval_end_x < 0
            && !sq->is_visible(veh->faction_id) && !random(8)) {
                tx = ts.rx;
                ty = ts.ry;
            }
        }
    }
    if (!random(4) && p.naval_start_x >= 0) {
        debug("trans_move_c %2d %2d -> %2d %2d\n", veh->x, veh->y, p.naval_start_x, p.naval_start_y);
        return set_move_to(id, p.naval_start_x, p.naval_start_y);
    }
    if (tx >= 0) {
        debug("trans_move_d %2d %2d -> %2d %2d\n", veh->x, veh->y, ts.rx, ts.ry);
        mapnodes.erase({tx, ty, NODE_PATROL});
        return set_move_to(id, tx, ty);
    }
    return mod_veh_skip(id);
}

int want_convoy(int faction, int x, int y, MAP* sq) {
    if (sq && sq->owner == faction && !mapnodes.count({x, y, NODE_CONVOY})
    && !(sq->items & BASE_DISALLOWED)) {
        int bonus = bonus_at(x, y);
        if (bonus == RES_ENERGY)
            return RES_NONE;
        else if (sq->items & (TERRA_CONDENSER | TERRA_SOIL_ENR))
            return RES_NUTRIENT;
        else if (bonus == RES_NUTRIENT)
            return RES_NONE;
        else if (sq->items & TERRA_MINE && sq->rocks & TILE_ROCKY)
            return RES_MINERAL;
        else if (sq->items & TERRA_FOREST && ~sq->items & TERRA_RIVER)
            return RES_MINERAL;
    }
    return RES_NONE;
}

int crawler_move(int id) {
    VEH* veh = &tx_vehicles[id];
    MAP* sq = mapsq(veh->x, veh->y);
    if (!sq || veh->home_base_id < 0) {
        return mod_veh_skip(id);
    }
    if (!at_target(veh)) {
        return SYNC;
    }
    BASE* base = &tx_bases[veh->home_base_id];
    int res = want_convoy(veh->faction_id, veh->x, veh->y, sq);
    bool prefer_min = base->nutrient_surplus > 5;
    int v1 = 0;
    if (res) {
        v1 = (sq->items & TERRA_FOREST ? 1 : 2);
    }
    if (res && v1 > 1) {
        return set_convoy(id, res);
    }
    int i = 0;
    int tx = -1;
    int ty = -1;
    TileSearch ts;
    ts.init(veh->x, veh->y, TS_TRIAD_LAND);

    while (++i < 50 && (sq = ts.get_next()) != NULL) {
        int other = unit_in_tile(sq);
        if (other > 0 && other != veh->faction_id) {
            continue;
        }
        res = want_convoy(veh->faction_id, ts.rx, ts.ry, sq);
        if (res && pm_safety[ts.rx][ts.ry] >= PM_SAFE) {
            int v2 = (sq->items & TERRA_FOREST ? 1 : 2);
            if (prefer_min && res == RES_MINERAL && v2 > 1) {
                return set_move_to(id, ts.rx, ts.ry);
            } else if (!prefer_min && res == RES_NUTRIENT) {
                return set_move_to(id, ts.rx, ts.ry);
            }
            if (res == RES_MINERAL && v2 > v1) {
                tx = ts.rx;
                ty = ts.ry;
                v1 = v2;
            }
        }
    }
    if (tx >= 0) {
        return set_move_to(id, tx, ty);
    }
    if (v1 > 0) {
        return set_convoy(id, RES_MINERAL);
    }
    return mod_veh_skip(id);
}

bool safe_path(const TileSearch& ts, int faction) {
    int i = 0;
    const PathNode* node = &ts.newtiles[ts.cur];

    while (node->dist > 0 && ++i < PathLimit) {
        assert(node->prev >= 0);
        MAP* sq = mapsq(node->x, node->y);
        if (pm_safety[node->x][node->y] < PM_SAFE) {
//            debug("path_unsafe %d %d %d\n", faction, node->x, node->y);
            return false;
        }
        if (sq && sq->owner > 0 && sq->owner != faction && !has_pact(faction, sq->owner)) {
//            debug("path_foreign %d %d %d\n", faction, node->x, node->y);
            return false;
        }
        node = &ts.newtiles[node->prev];
    }
    return true;
}

bool valid_colony_path(int id) {
    VEH* veh = &tx_vehicles[id];
    int faction = veh->faction_id;
    int tx = veh->waypoint_1_x;
    int ty = veh->waypoint_1_y;

    if (at_target(veh) || !can_build_base(tx, ty, faction, veh_triad(id))) {
        return false;
    }
    if (~veh->state & VSTATE_UNK_40000 && (veh->state & VSTATE_UNK_2000
    || map_range(veh->x, veh->y, tx, ty) > 10)) {
        return false;
    }
    return true;
}

bool can_build_base(int x, int y, int faction, int triad) {
    if ((x + y)%2) // Invalid map coordinates
        return false;
    MAP* sq = mapsq(x, y);
    if (!sq || y < 3 || y >= *map_axis_y-3 || (~sq->landmarks & LM_JUNGLE && pm_former[x][y] > 0))
        return false;
    if ((sq->rocks & TILE_ROCKY && !is_ocean(sq)) || (sq->items & (BASE_DISALLOWED | IMP_ADVANCED)))
        return false;
    if (sq->owner > 0 && faction != sq->owner && !at_war(faction, sq->owner))
        return false;
    if (non_ally_in_tile(faction, sq))
        return false;
    if (sq->landmarks & LM_VOLCANO && sq->art_ref_id == 0)
        return false;
    if (sq->landmarks & LM_JUNGLE && !is_ocean(sq) && *current_turn > 60) {
        if (bases_in_range(x, y, 1) > 0 || bases_in_range(x, y, 2) > 1) {
            return false;
        }
    } else if (bases_in_range(x, y, 2) > 0) {
        return false;
    }
    if (triad != TRIAD_SEA && !is_ocean(sq)) {
        return true;
    } else if ((triad == TRIAD_SEA || triad == TRIAD_AIR) && is_ocean_shelf(sq)) {
        return true;
    }
    return false;
}

int base_tile_score(int x1, int y1, int range, int triad) {
    const int priority[][2] = {
        {TERRA_RIVER, 1},
        {TERRA_FUNGUS, -2},
        {TERRA_FARM, 2},
        {TERRA_FOREST, 2},
        {TERRA_MONOLITH, 4},
    };
    MAP* sq = mapsq(x1, y1);
    int score = (!is_ocean(sq) && sq->items & TERRA_RIVER ? 4 : 0);
    int land = 0;
    range *= (triad == TRIAD_LAND ? 3 : 1);

    for (int i=1; i<=20; i++) {
        int x2 = wrap(x1 + TableOffsetX[i]);
        int y2 = y1 + TableOffsetY[i];
        sq = mapsq(x2, y2);
        if (sq) {
            int items = sq->items;
            score += (bonus_at(x2, y2) ? 6 : 0);
            if (sq->landmarks && !(sq->landmarks & (LM_DUNES | LM_SARGASSO | LM_UNITY))) {
                score += (sq->landmarks & LM_JUNGLE ? 3 : 2);
            }
            if (i < 8) { // Only adjacent tiles
                if (triad == TRIAD_SEA && !is_ocean(sq)
                && nearby_tiles(x2, y2, TRIAD_LAND, 20) >= 20 && ++land < 3) {
                    score += (sq->owner < 1 ? 20 : 3);
                }
                if (is_ocean_shelf(sq)) {
                    score += (triad == TRIAD_SEA ? 3 : 2);
                }
            }
            if (!is_ocean(sq)) {
                if (sq->level & TILE_RAINY) {
                    score += 2;
                }
                if (sq->level & TILE_MOIST && sq->rocks & TILE_ROLLING) {
                    score += 2;
                }
            }
            for (const int* p : priority) if (items & p[0]) score += p[1];
        }
    }
    return score - range + random(4) + min(0, pm_safety[x1][y1]);
}

int colony_move(int id) {
    VEH* veh = &tx_vehicles[id];
    MAP* sq = mapsq(veh->x, veh->y);
    int faction = veh->faction_id;
    int triad = veh_triad(id);
    if (defend_tile(veh, sq) || veh->iter_count > 7) {
        return mod_veh_skip(id);
    }
    if (pm_safety[veh->x][veh->y] < PM_SAFE) {
        return escape_move(id);
    }
    if ((at_target(veh) || triad == TRIAD_LAND || !random(12))
    && can_build_base(veh->x, veh->y, faction, triad)) {
        action_build(id, 0);
        return SYNC;
    }
    if (is_ocean(sq) && triad == TRIAD_LAND) {
        if (!has_transport(veh->x, veh->y, faction)) {
            mapnodes.insert({veh->x, veh->y, NODE_NEED_FERRY});
            return mod_veh_skip(id);
        }
        for (const int* t : NearbyTiles) {
            int x2 = wrap(veh->x + t[0]);
            int y2 = veh->y + t[1];
            if (non_combat_move(x2, y2, faction, triad) && has_base_sites(x2, y2, faction, TRIAD_LAND)) {
                debug("colony_trans %d %d -> %d %d\n", veh->x, veh->y, x2, y2);
                return set_move_to(id, x2, y2);
            }
        }
    }
    if (!valid_colony_path(id)) {
        int i = 0;
        int k = 0;
        int tscore = INT_MIN;
        int tx = -1;
        int ty = -1;
        int limit = (!((*current_turn + id) % 8) ? 500 : 200);
        TileSearch ts;
        ts.init(veh->x, veh->y, triad, 2);
        while (++i < limit && k < 30 && (sq = ts.get_next()) != NULL) {
            if (!can_build_base(ts.rx, ts.ry, faction, triad) || !safe_path(ts, faction))
                continue;
            int score = base_tile_score(ts.rx, ts.ry, ts.dist, triad);
            k++;
            if (score > tscore) {
                tx = ts.rx;
                ty = ts.ry;
                tscore = score;
            }
        }
        if (tx >= 0) {
            debug("colony_move %d %d -> %d %d | %d %d\n", veh->x, veh->y, tx, ty, faction, tscore);
            adjust_value(pm_former, tx, ty, 1, 1);
            // Set these flags to disable any non-Thinker unit automation.
            veh->state |= VSTATE_UNK_40000;
            veh->state &= ~VSTATE_UNK_2000;
            return set_move_to(id, tx, ty);
        } else if (limit == 500) {
            debug("disband colony %d\n", id);
            return veh_kill(id);
        }
    }
    if (!at_target(veh)) {
        return SYNC;
    }
    if (triad == TRIAD_LAND) {
        return enemy_move(id);
    }
    return mod_veh_skip(id);
}

bool can_bridge(int x, int y, int faction, MAP* sq) {
    if (is_ocean(sq) || !has_terra(faction, FORMER_RAISE_LAND, 0)) {
        return false;
    }
    if (is_shore_level(sq) && mapnodes.count({x, y, NODE_GOAL_RAISE_LAND})) {
        return true;
    }
    if (coast_tiles(x, y) < 3) {
        return false;
    }
    const int range = 4;
    TileSearch ts;
    ts.init(x, y, TRIAD_LAND);
    int k = 0;
    while (++k < 120 && ts.get_next() != NULL);

    int n = 0;
    for (int i=-range*2; i<=range*2; i++) {
        for (int j=-range*2 + abs(i); j<=range*2 - abs(i); j+=2) {
            int x2 = wrap(x + i);
            int y2 = y + j;
            sq = mapsq(x2, y2);
            if (sq && y2 > 0 && y2 < *map_axis_y-1 && !is_ocean(sq)
            && !ts.oldtiles.count({x2, y2})) {
                n++;
                if (sq->owner > 0 && sq->owner != faction
                && faction_might(faction) < faction_might(sq->owner)) {
                    return false;
                }
            }
        }
    }
    debug("bridge %d x: %d y: %d tiles: %d\n", faction, x, y, n);
    return n > 4;
}

bool can_borehole(int x, int y, int faction, int bonus, MAP* sq) {
    if (!has_terra(faction, FORMER_THERMAL_BORE, is_ocean(sq)))
        return false;
    if (!sq || sq->items & (BASE_DISALLOWED | IMP_ADVANCED) || bonus == RES_NUTRIENT)
        return false;
    // Planet factions should build boreholes only in reduced numbers.
    if (tx_factions[faction].SE_planet_base > 0 && (map_hash(x, y) % 101 > 14))
        return false;
    if (bonus == RES_NONE && sq->rocks & TILE_ROLLING)
        return false;
    if (pm_former[x][y] < 4 && !mapnodes.count({x, y, NODE_BOREHOLE}))
        return false;
    int level = sq->level >> 5;
    for (const int* t : NearbyTiles) {
        int x2 = wrap(x + t[0]);
        int y2 = y + t[1];
        sq = mapsq(x2, y2);
        if (!sq || sq->items & TERRA_THERMAL_BORE || mapnodes.count({x2, y2, NODE_BOREHOLE})) {
            return false;
        }
        int level2 = sq->level >> 5;
        if (level2 < level && level2 > LEVEL_OCEAN_SHELF) {
            return false;
        }
    }
    return true;
}

bool can_farm(int x, int y, int faction, int bonus, bool has_nut, MAP* sq) {
    bool rain = sq->level & (TILE_RAINY | TILE_MOIST);
    if (!has_terra(faction, FORMER_FARM, is_ocean(sq)))
        return false;
    if (bonus == RES_NUTRIENT && (has_nut || (rain && sq->rocks & TILE_ROLLING)))
        return true;
    if (bonus == RES_ENERGY || bonus == RES_MINERAL)
        return false;
    if (sq->landmarks & LM_JUNGLE && !has_nut)
        return false;
    if (nearby_items(x, y, 1, TERRA_FOREST) < (sq->items & TERRA_FOREST ? 4 : 1))
        return false;
    if (!has_nut && nearby_items(x, y, 1, TERRA_FARM | TERRA_SOLAR) > 2)
        return false;
    if (rain && sq->rocks & TILE_ROLLING)
        return nearby_items(x, y, 1, TERRA_FARM | TERRA_CONDENSER) < 3;
    return (has_nut && !(x % 2) && !(y % 2) && !(abs(x-y) % 4));
}

bool can_fungus(int x, int y, int faction, int bonus, MAP* sq) {
    if (sq->items & (TERRA_BASE_IN_TILE | TERRA_MONOLITH | IMP_ADVANCED))
        return false;
    return !can_borehole(x, y, faction, bonus, sq) && nearby_items(x, y, 1, TERRA_FUNGUS) < 5;
}

bool can_road(int x, int y, int faction, MAP* sq) {
    assert(faction > 0 && faction < 8);
    if (is_ocean(sq) || !has_terra(faction, FORMER_ROAD, 0)
    || sq->items & (TERRA_ROAD | TERRA_BASE_IN_TILE))
        return false;
    if (~sq->items & TERRA_BASE_RADIUS && pm_roads[x][y] < 1)
        return false;
    if (sq->items & TERRA_FUNGUS && (!has_tech(faction, tx_basic->tech_preq_build_road_fungus)
    || (!build_tubes && has_project(faction, FAC_XENOEMPATHY_DOME))))
        return false;
    if (mapnodes.count({x, y, NODE_GOAL_RAISE_LAND}))
        return true;
    if (pm_roads[x][y] > 0 || sq->items & (TERRA_FARM | TERRA_MINE | TERRA_CONDENSER | TERRA_THERMAL_BORE))
        return true;
    int i = 0;
    int r[] = {0,0,0,0,0,0,0,0};
    for (const int* t : NearbyTiles) {
        sq = mapsq(wrap(x + t[0]), y + t[1]);
        if (!is_ocean(sq) && sq->owner == faction) {
            if (sq->items & (TERRA_ROAD | TERRA_BASE_IN_TILE)) {
                r[i] = 1;
            }
        }
        i++;
    }
    // Determine if we should connect roads on opposite sides of the tile
    if ((r[0] && r[4] && !r[2] && !r[6])
    || (r[2] && r[6] && !r[0] && !r[4])
    || (r[1] && r[5] && !((r[2] && r[4]) || (r[0] && r[6])))
    || (r[3] && r[7] && !((r[0] && r[2]) || (r[4] && r[6])))) {
        return true;
    }
    return false;
}

bool can_magtube(int x, int y, int faction, MAP* sq) {
    assert(faction > 0 && faction < 8);
    if (is_ocean(sq) || pm_roads[x][y] < 1 || sq->items & (TERRA_MAGTUBE | TERRA_BASE_IN_TILE)) {
        return false;
    }
    return has_terra(faction, FORMER_MAGTUBE, 0) && sq->items & TERRA_ROAD
        && (~sq->items & TERRA_FUNGUS || has_tech(faction, tx_basic->tech_preq_build_road_fungus));
}

bool can_sensor(int x, int y, int faction, MAP* sq) {
    assert(faction > 0 && faction < 8);
    return has_terra(faction, FORMER_SENSOR, is_ocean(sq))
        && ~sq->items & TERRA_SENSOR
        && !nearby_items(x, y, 2, TERRA_SENSOR)
        && (~sq->items & TERRA_FUNGUS || has_tech(faction, tx_basic->tech_preq_improv_fungus))
        && *current_turn > random(20);
}

int select_item(int x, int y, int faction, MAP* sq) {
    int items = sq->items;
    bool sea = is_ocean(sq);
    if (items & TERRA_BASE_IN_TILE || (sea && !is_ocean_shelf(sq))
    || (sq->landmarks & LM_VOLCANO && sq->art_ref_id == 0)) {
        return -1;
    }
    int bonus = bonus_at(x, y);
    bool rocky_sq = sq->rocks & TILE_ROCKY;
    bool has_eco = has_terra(faction, FORMER_CONDENSER, 0);
    bool has_min = has_tech(faction, tx_basic->tech_preq_allow_3_minerals_sq);
    bool has_nut = has_tech(faction, tx_basic->tech_preq_allow_3_nutrients_sq);
    bool road = can_road(x, y, faction, sq);

    if (can_magtube(x, y, faction, sq)) {
        return FORMER_MAGTUBE;
    }
    if (items & TERRA_FUNGUS) {
        if (plans[faction].keep_fungus && can_fungus(x, y, faction, bonus, sq)) {
            if (road)
                return FORMER_ROAD;
            else if (can_sensor(x, y, faction, sq))
                return FORMER_SENSOR;
            return -1;
        }
        return FORMER_REMOVE_FUNGUS;
    }
    if (can_bridge(x, y, faction, sq)) {
        int cost = terraform_cost(x, y, faction);
        if (mapnodes.count({x, y, NODE_RAISE_LAND}) || cost < tx_factions[faction].energy_credits/8) {
            return (road ? FORMER_ROAD : FORMER_RAISE_LAND);
        }
    }
    if (~items & TERRA_BASE_RADIUS || items & (TERRA_MONOLITH | TERRA_FUNGUS)) {
        return (road ? FORMER_ROAD : -1);
    }
    if (road) {
        return FORMER_ROAD;
    }
    if (plans[faction].plant_fungus && can_fungus(x, y, faction, bonus, sq)) {
        return FORMER_PLANT_FUNGUS;
    }
    if (sea) {
        bool improved = items & (TERRA_MINE | TERRA_SOLAR | TERRA_SENSOR);
        if (~items & TERRA_FARM && has_terra(faction, FORMER_FARM, sea))
            return FORMER_FARM;
        else if (!improved && bonus == RES_NONE && can_sensor(x, y, faction, sq))
            return FORMER_SENSOR;
        else if (!improved && has_terra(faction, FORMER_SOLAR, sea) && bonus != RES_MINERAL
        && (bonus == RES_NUTRIENT || nearby_items(x, y, 1, TERRA_SOLAR)+1 < nearby_items(x, y, 1, TERRA_MINE)))
            return FORMER_SOLAR;
        else if (!improved && has_terra(faction, FORMER_MINE, sea))
            return FORMER_MINE;
        return -1;
    }
    if ((has_min || bonus != RES_NONE) && can_borehole(x, y, faction, bonus, sq))
        return FORMER_THERMAL_BORE;
    if (items & TERRA_THERMAL_BORE)
        return -1;
    if (rocky_sq && ~items & TERRA_MINE && (has_min || bonus == RES_MINERAL)
    && has_terra(faction, FORMER_MINE, sea))
        return FORMER_MINE;
    if (rocky_sq && (bonus == RES_NUTRIENT || sq->landmarks & LM_JUNGLE)
    && has_terra(faction, FORMER_LEVEL_TERRAIN, sea))
        return FORMER_LEVEL_TERRAIN;
    if (!rocky_sq && can_farm(x, y, faction, bonus, has_nut, sq)) {
        bool improved = items & (TERRA_CONDENSER | TERRA_SOLAR);
        if (!has_nut) {
            if (!improved && sq->level & TILE_RAINY && has_terra(faction, FORMER_SOLAR, sea))
                return FORMER_SOLAR;
            else if (~items & TERRA_FARM && sq->level & TILE_MOIST && sq->rocks & TILE_ROLLING)
                return FORMER_FARM;
        }
        if (has_nut || bonus == RES_NUTRIENT) {
            if (~items & TERRA_FARM)
                return FORMER_FARM;
            else if (~items & TERRA_CONDENSER && has_eco)
                return FORMER_CONDENSER;
            else if (~items & TERRA_SOIL_ENR && has_terra(faction, FORMER_SOIL_ENR, sea))
                return FORMER_SOIL_ENR;
            else if (!has_eco && !improved && has_terra(faction, FORMER_SOLAR, sea)
            && (bonus != RES_NONE || items & TERRA_RIVER))
                return FORMER_SOLAR;
        }
    } else if (!rocky_sq && !(items & IMP_ADVANCED)) {
        if (can_sensor(x, y, faction, sq))
            return FORMER_SENSOR;
        else if (~items & TERRA_FOREST && has_terra(faction, FORMER_FOREST, sea))
            return FORMER_FOREST;
    }
    return -1;
}

int former_tile_score(int x1, int y1, int x2, int y2, int faction, MAP* sq) {
    const int priority[][2] = {
        {TERRA_RIVER, 2},
        {TERRA_FARM, -3},
        {TERRA_SOLAR, -2},
        {TERRA_FOREST, -4},
        {TERRA_MINE, -4},
        {TERRA_CONDENSER, -4},
        {TERRA_SOIL_ENR, -4},
        {TERRA_THERMAL_BORE, -8},
    };
    int bonus = bonus_at(x2, y2);
    int range = map_range(x1, y1, x2, y2);
    int items = sq->items;
    int score = (sq->landmarks ? 3 : 0);

    if (bonus && !(items & IMP_ADVANCED)) {
        bool bh = (bonus == RES_MINERAL || bonus == RES_ENERGY) && can_borehole(x2, y2, faction, bonus, sq);
        int w = (bh || !(items & IMP_SIMPLE) ? 5 : 1);
        score += w * (bonus == RES_NUTRIENT ? 3 : 2);
    }
    for (const int* p : priority) {
        if (items & p[0]) {
            score += p[1];
        }
    }
    if (items & TERRA_FUNGUS) {
        score += (items & IMP_ADVANCED ? 20 : 0);
        score += (plans[faction].keep_fungus ? -10 : -2);
        score += (plans[faction].plant_fungus && (items & TERRA_ROAD) ? -8 : 0);
    }
    if (items & (TERRA_FOREST | TERRA_SENSOR) && can_road(x2, y2, faction, sq)) {
        score += 8;
    }
    if (pm_roads[x2][y2] > 0 && (~items & TERRA_ROAD || (build_tubes && ~items & TERRA_MAGTUBE))) {
        score += 12;
    }
    if (is_shore_level(sq) && mapnodes.count({x2, y2, NODE_GOAL_RAISE_LAND})) {
        score += 20;
    }
    return score - range/2 + min(8, pm_former[x2][y2]) + min(0, pm_safety[x2][y2]);
}

int former_move(int id) {
    VEH* veh = &tx_vehicles[id];
    int faction = veh->faction_id;
    int triad = veh_triad(id);
    int x = veh->x;
    int y = veh->y;
    MAP* sq = mapsq(x, y);
    bool safe = pm_safety[x][y] >= PM_SAFE;
    int item;
    if (!sq || sq->owner != faction) {
        return enemy_move(id);
    }
    if (defend_tile(veh, sq)) {
        return mod_veh_skip(id);
    }
    if (safe || (veh->move_status >= 16 && veh->move_status < 22)) {
        if ((veh->move_status >= 4 && veh->move_status < 24)
        || (triad != TRIAD_LAND && !at_target(veh))) {
            return SYNC;
        }
        item = select_item(x, y, faction, sq);
        if (item >= 0) {
            int cost = 0;
            pm_former[x][y] -= 2;
            if (item == FORMER_RAISE_LAND && !mapnodes.count({x, y, NODE_RAISE_LAND})) {
                cost = terraform_cost(x, y, faction);
                tx_factions[faction].energy_credits -= cost;
            }
            debug("former_action %d x: %d y: %d act: %d cost: %d %s\n",
                faction, x, y, id, cost, tx_terraform[item].name);
            return set_action(id, item+4, *tx_terraform[item].shortcuts);
        }
    } else if (!safe) {
        return escape_move(id);
    }
    int i = 0;
    int limit = (!((*current_turn + id) % 8) ? 200 : 50);
    int tscore = INT_MIN;
    int action = -1;
    int tx = -1;
    int ty = -1;
    int bx = x;
    int by = y;
    if (veh->home_base_id >= 0) {
        bx = tx_bases[veh->home_base_id].x;
        by = tx_bases[veh->home_base_id].y;
    }
    TileSearch ts;
    ts.init(x, y, triad);

    while (++i < limit && (sq = ts.get_next()) != NULL) {
        if (sq->owner != faction || sq->items & TERRA_BASE_IN_TILE
        || pm_safety[ts.rx][ts.ry] < PM_SAFE
        || (pm_former[ts.rx][ts.ry] < 1 && pm_roads[ts.rx][ts.ry] < 1)
        || other_in_tile(faction, sq))
            continue;
        int score = former_tile_score(bx, by, ts.rx, ts.ry, faction, sq);
        if (score > tscore && (item = select_item(ts.rx, ts.ry, faction, sq)) != -1) {
            tx = ts.rx;
            ty = ts.ry;
            tscore = score;
            action = item;
        }
    }
    if (tx >= 0) {
        pm_former[tx][ty] -= 2;
        debug("former_move %d %d -> %d %d | %d %d | %d %s\n",
            x, y, tx, ty, faction, id, tscore, (action >= 0 ? tx_terraform[action].name : ""));
        return set_move_to(id, tx, ty);
    } else if (!random(4)) {
        return set_move_to(id, bx, by);
    } else if (limit == 200) {
        debug("disband former %d\n", id);
        return veh_kill(id);
    }
    debug("former_skip %d %d | %d %d\n", x, y, faction, id);
    return mod_veh_skip(id);
}

int choose_defender(int x, int y, int faction, int att_id) {
    int id = veh_at(x, y);
    if (id < 0 || !tx_vehicles[id].is_visible(faction)) {
        return -1;
    }
    return best_defender(id, att_id, 0);
}

int combat_value(int id, int power, int moves, int mov_rate) {
    VEH* veh = &tx_vehicles[id];
    return max(1, power * (10 - veh->damage_taken) * min(moves, mov_rate) / mov_rate);
}

double battle_eval(int id1, int id2, int moves, int mov_rate) {
    int s1;
    int s2;
    battle_compute(id1, id2, (int)&s1, (int)&s2, 0);
    int v1 = combat_value(id1, s1, moves, mov_rate);
    int v2 = combat_value(id2, s2, mov_rate, mov_rate);
    return 1.0 * v1/v2;
}

int combat_move(int id) {
    VEH* veh = &tx_vehicles[id];
    MAP* sq = mapsq(veh->x, veh->y);
    UNIT* u = &tx_units[veh->proto_id];
    AIPlans& p = plans[veh->faction_id];
    int faction = veh->faction_id;
    int triad = unit_triad(veh->proto_id);
    assert(veh->is_combat_unit());
    if (veh->state & VSTATE_IN_TRANSPORT) {
        return (veh->iter_count < 2 ? SYNC : mod_veh_skip(id));
    }
    bool combat = ~u->ability_flags & ABL_ARTILLERY && pm_enemy_near[veh->x][veh->y] > 0;
    if (veh->iter_count > 7 || (!combat && need_heals(veh))) {
        return escape_move(id);
    }
    bool at_base = sq->items & TERRA_BASE_IN_TILE;
    int veh_region = sq->region;
    int mov_rate = tx_basic->mov_rate_along_roads;
    int moves = mod_veh_speed(id) - veh->road_moves_spent;
    int max_dist = moves;
    int defenders = 0;

    if (at_base) {
        for (int k=0; k < *total_num_vehicles; k++) {
            VEH* v = &tx_vehicles[k];
            if (veh->x == v->x && veh->y == v->y && v->damage_taken < 5
            && v->move_status != ORDER_SENTRY_BOARD
            && v->weapon_type() <= WPN_PSI_ATTACK) {
                defenders++;
            }
        }
        max_dist = (defenders > 1 ? moves : 1);
    }

    int i = 0;
    int tx = -1;
    int ty = -1;
    int id2 = -1;
    int type = (triad == TRIAD_LAND && at_base ? TS_NEAR_ROADS : triad);
    double odds = (at_base ? 1.55 - 0.15 * min(3, defenders) : 1.1);
    TileSearch ts;
    ts.init(veh->x, veh->y, type);

    while (combat && ++i < 50 && (sq = ts.get_next()) != NULL && ts.dist <= max_dist) {
        bool to_base = sq->items & TERRA_BASE_IN_TILE;
        int faction2 = unit_in_tile(sq);
        assert(veh->x != ts.rx || veh->y != ts.ry);
        assert(map_range(veh->x, veh->y, ts.rx, ts.ry) <= ts.dist);
        assert((at_base && to_base) < ts.dist);

        if (at_war(faction, faction2) && (id2 = choose_defender(ts.rx, ts.ry, faction, id)) != -1) {
            VEH* veh2 = &tx_vehicles[id2];
            UNIT* u2 = &tx_units[veh2->proto_id];
            max_dist = ts.dist;
            if (ts.dist > 1 && !veh2->is_visible(faction)) {
                continue;
            }
            if (!to_base && veh_triad(id2) == TRIAD_AIR && ~u->ability_flags & ABL_AIR_SUPERIORITY) {
                continue;
            }
            double v1 = battle_eval(id, id2, moves - ts.dist + 1, mov_rate);
            double v2 = (sq->owner == faction ? 0.1 : 0.0)
                + (to_base || !conf.collateral_damage_value ? 0.0 : 0.05 * (pm_enemy[ts.rx][ts.ry]))
                + min(12, abs(offense_value(u2)))*(u2->chassis_type == CHS_INFANTRY ? 0.008 : 0.02);
            double v3 = min(1.6, v1) + min(0.5, max(-0.5, v2));

            debug("attack_odds %2d %2d -> %2d %2d | %d %d %d %d | %d %d %.4f %.4f %.4f %.4f | %d %d %s | %d %d %s\n",
                veh->x, veh->y, ts.rx, ts.ry, ts.dist, max_dist, at_base, to_base,
                pm_enemy[ts.rx][ts.ry], pm_safety[ts.rx][ts.ry], v1, v2, v3, odds,
                id, faction, u->name, id2, faction2, u2->name);
            if (v3 > odds) {
                tx = ts.rx;
                ty = ts.ry;
                odds = v3;
            }
        } else if (to_base && at_war(faction, sq->owner) && pm_enemy[ts.rx][ts.ry] < 1) {
            tx = ts.rx;
            ty = ts.ry;
            break;
        } else if (faction2 < 0 && mapnodes.count({ts.rx, ts.ry, NODE_PATROL})) {
            tx = ts.rx;
            ty = ts.ry;
            max_dist = ts.dist;
        } else if (faction2 < 0 && tx < 0 && !sq->is_visible(faction) && !random(8)) {
            tx = ts.rx;
            ty = ts.ry;
        }
    }
    if (tx >= 0) {
        debug("attack_set  %2d %2d -> %2d %2d\n", veh->x, veh->y, tx, ty);
        mapnodes.erase({tx, ty, NODE_PATROL});
        return set_move_to(id, tx, ty);
    }
    if (need_heals(veh)) {
        return escape_move(id);
    }
    // Check if the unit should move to stackup point or board naval transport
    int px = p.naval_start_x;
    int py = p.naval_start_y;

    if (triad == TRIAD_LAND && px >= 0
    && (!at_base || defenders > 1)
    && veh_region == p.main_region
    && p.transports > 1
    && !(id % (p.prioritize_naval ? 2 : 4))) {
        pm_former[px][py]--;
        if (veh->x == px && veh->y == py) {
            for (int k=0; k < *total_num_vehicles; k++) {
                VEH* v = &tx_vehicles[k];
                if (veh->x == v->x && veh->y == v->y
                && veh_triad(k) == TRIAD_SEA
                && veh->weapon_type() == WPN_TROOP_TRANSPORT
                && cargo_loaded(k) < cargo_capacity(k)) {
                    return set_board_to(id, k);
                }
            }
            if ((*current_turn + id) % 8) {
                return mod_veh_skip(id);
            }
        } else if (pm_former[px][py] >= -(p.transports > 5 ? 10 : 5)) {
            return set_move_to(id, px, py);
        }
    }
    // Provide cover for naval invasion ships
    if (triad == TRIAD_SEA && px >= 0
    && (!at_base || defenders > 1)
    && veh_region == p.main_sea_region
    && !(id % (p.prioritize_naval ? 2 : 4))) {
        return set_move_to(id, p.naval_end_x, p.naval_end_y);
    }
    if (at_base && defenders < 2) {
        return mod_veh_skip(id);
    }
    return enemy_move(id);
}



