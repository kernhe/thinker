
#include "game.h"


char* prod_name(int prod) {
    if (prod < 0)
        return (char*)(tx_facilities[-prod].name);
    else
        return (char*)&(tx_units[prod].name);
}

int mineral_cost(int fac, int prod) {
    if (prod >= 0)
        return tx_units[prod].cost * tx_cost_factor(fac, 1, -1);
    else
        return tx_facilities[-prod].cost * tx_cost_factor(fac, 1, -1);
}

bool knows_tech(int fac, int tech) {
    return tx_tech_discovered[tech] & (1 << fac);
}

int unit_triad(int id) {
    return tx_chassis[tx_units[id].chassis_type].triad;
}

int offense_value(UNIT* u) {
    if (u->weapon_type == WPN_CONVENTIONAL_PAYLOAD)
        return tx_factions[*tx_active_faction].best_weapon_value * u->reactor_type;
    return tx_weapon[u->weapon_type].offense_value * u->reactor_type;
}

int defense_value(UNIT* u) {
    return tx_defense[u->armor_type].defense_value * u->reactor_type;
}

int random(int n) {
    return rand() % (n != 0 ? n : 1);
}

int wrap(int a, int b) {
    return (a < 0 ? a + b : a);
}

int map_range(int x1, int y1, int x2, int y2) {
    int xd = abs(x1-x2);
    int yd = abs(y1-y2);
    if (xd > *tx_map_axis_x/2)
        xd = *tx_map_axis_x - xd;
    return (xd + yd)/2;
}

MAP* mapsq(int x, int y) {
    int i = x/2 + (*tx_map_half_x) * y;
    if (i >= 0 && i < *tx_map_half_x * *tx_map_axis_y)
        return &((*tx_map_ptr)[i]);
    else
        return NULL;
}

int unit_in_tile(MAP* sq) {
    if (!sq || (sq->flags & 0xf) == 0xf)
        return -1;
    return sq->flags & 0xf;
}

bool water_base(int id) {
    MAP* sq = mapsq(tx_bases[id].x_coord, tx_bases[id].y_coord);
    return (sq && sq->altitude < ALTITUDE_MIN_LAND);
}

bool convoy_not_used(int x, int y) {
    for (int i=0; i<*tx_total_num_vehicles; i++) {
        VEH* veh = &tx_vehicles[i];
        if (veh->x_coord == x && veh->y_coord == y && veh->move_status == STATUS_CONVOY) {
            return false;
        }
    }
    return true;
}

bool workable_tile(int x, int y, int fac) {
    MAP* tile;
    for (const int* t : offset_20) {
        int x2 = wrap(x + t[0], *tx_map_axis_x);
        int y2 = y + t[1];
        tile = mapsq(x2, y2);
        if (tile && tile->owner == fac && tile->built_items & TERRA_BASE_IN_TILE) {
            return true;
        }
    }
    return false;
}

int coast_tiles(int x, int y) {
    MAP* tile;
    int n = 0;
    for (const int* t : offset) {
        tile = mapsq(wrap(x + t[0], *tx_map_axis_x), y + t[1]);
        if (tile && tile->altitude < ALTITUDE_MIN_LAND) {
            n++;
        }
    }
    return n;
}

void TileSearch::init(int x, int y, int tp) {
    head = 0;
    tail = 0;
    items = 0;
    type = tp;
    oldtiles.clear();
    tile = mapsq(x, y);
    if (tile) {
        items++;
        int p = x | y << 16;
        oldtiles.insert(mp(x, y));
        newtiles[0] = p;
    }
}

int TileSearch::visited() {
    return oldtiles.size();
}

MAP* TileSearch::get_next() {
    while (items > 0) {
        int p = newtiles[head];
        head = (head + 1) % QSIZE;
        items--;
        cur_x = p & 0xffff;
        cur_y = p >> 16;
        if (!(tile = mapsq(cur_x, cur_y)))
            continue;
        bool skip = (type == LAND_ONLY && tile->altitude < ALTITUDE_MIN_LAND) ||
                    (type == WATER_ONLY && tile->altitude >= ALTITUDE_MIN_LAND);
        if (oldtiles.size() > 1 && skip)
            continue;
        for (const int* t : offset) {
            int x2 = wrap(cur_x + t[0], *tx_map_axis_x);
            int y2 = cur_y + t[1];
            p = x2 | y2 << 16;
            if (items < QSIZE && y2 >= 0 && y2 < *tx_map_axis_y && oldtiles.count(mp(x2, y2)) == 0) {
                newtiles[tail] = p;
                tail = (tail + 1) % QSIZE;
                items++;
                oldtiles.insert(mp(x2, y2));
            }
        }
        return tile;
    }
    return NULL;
}



