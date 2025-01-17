
#include "faction.h"


bool has_tech(int tech_id, int faction) {
    assert(valid_player(faction));
    assert(tech_id >= TECH_Disable && tech_id <= TECH_TranT);
    if (tech_id == TECH_None) {
        return true;
    }
    return tech_id >= 0 && TechOwners[tech_id] & (1 << faction);
}

bool has_chassis(int faction, VehChassis chs) {
    return has_tech(Chassis[chs].preq_tech, faction);
}

bool has_weapon(int faction, VehWeapon wpn) {
    return has_tech(Weapon[wpn].preq_tech, faction);
}

bool has_wmode(int faction, VehWeaponMode mode) {
    for (int i = 0; i < MaxWeaponNum; i++) {
        if (Weapon[i].mode == mode && has_tech(Weapon[i].preq_tech, faction)) {
            return true;
        }
    }
    return false;
}

bool has_aircraft(int faction) {
    return has_chassis(faction, CHS_NEEDLEJET) || has_chassis(faction, CHS_COPTER)
        || has_chassis(faction, CHS_GRAVSHIP);
}

bool has_ships(int faction) {
    return has_chassis(faction, CHS_FOIL) || has_chassis(faction, CHS_CRUISER);
}

bool has_orbital_drops(int faction) {
    return has_tech(Rules->tech_preq_orb_insert_wo_space, faction)
        || has_project(FAC_SPACE_ELEVATOR, faction);
}

bool has_terra(int faction, FormerItem act, bool ocean) {
    int preq_tech = (ocean ? Terraform[act].preq_tech_sea : Terraform[act].preq_tech);
    if ((act == FORMER_RAISE_LAND || act == FORMER_LOWER_LAND)
    && *game_rules & RULES_SCN_NO_TERRAFORMING) {
        return false;
    }
    if (act >= FORMER_CONDENSER && act <= FORMER_LOWER_LAND
    && has_project(FAC_WEATHER_PARADIGM, faction)) {
        return preq_tech != TECH_Disable;
    }
    return has_tech(preq_tech, faction);
}

bool has_project(FacilityId item_id, int faction) {
    /* If faction_id is negative, check if anyone has built the project. */
    assert(faction < MaxPlayerNum && item_id >= SP_ID_First && item_id <= FAC_EMPTY_SP_64);
    int i = SecretProjects[item_id - SP_ID_First];
    return i >= 0 && (faction < 0 || Bases[i].faction_id == faction);
}

int facility_count(FacilityId item_id, int faction) {
    assert(valid_player(faction) && item_id < SP_ID_First);
    int n = 0;
    for (int i=0; i < *total_num_bases; i++) {
        BASE* base = &Bases[i];
        if (base->faction_id == faction && has_fac_built(item_id, i)) {
            n++;
        }
    }
    return n;
}

int prod_count(int item_id, int faction, int base_skip_id) {
    /* Prototypes must be predefined units or created by the faction. */
    assert(valid_player(faction));
    assert(item_id < 0
        || item_id/MaxProtoFactionNum == 0
        || item_id/MaxProtoFactionNum == faction);
    int n = 0;
    for (int i=0; i < *total_num_bases; i++) {
        BASE* base = &Bases[i];
        if (base->faction_id == faction
        && base->item() == item_id
        && i != base_skip_id) {
            n++;
        }
    }
    return n;
}


/*
Determine if the specified faction is controlled by a human player or computer AI.
*/
bool is_human(int faction) {
    return FactionStatus[0] & (1 << faction);
}

/*
Determine if the specified faction is alive or whether they've been eliminated.
*/
bool is_alive(int faction) {
    return FactionStatus[1] & (1 << faction);
}

/*
Determine if the specified faction is a Progenitor faction (Caretakers / Usurpers).
*/
bool is_alien(int faction) {
    return *expansion_enabled && MFactions[faction].rule_flags & RFLAG_ALIEN;
}

/*
Exclude native life since Thinker AI routines don't apply to them.
*/
bool thinker_enabled(int faction) {
    return faction > 0 && !is_human(faction) && faction <= conf.factions_enabled;
}

bool at_war(int faction1, int faction2) {
    return faction1 != faction2 && faction1 >= 0 && faction2 >= 0
        && Factions[faction1].diplo_status[faction2] & DIPLO_VENDETTA;
}

bool has_pact(int faction1, int faction2) {
    return faction1 >= 0 && faction2 >= 0
        && Factions[faction1].diplo_status[faction2] & DIPLO_PACT;
}

bool has_treaty(int faction1, int faction2, uint32_t treaty) {
    return faction1 >= 0 && faction2 >= 0
        && Factions[faction1].diplo_status[faction2] & treaty;
}

bool has_agenda(int faction1, int faction2, uint32_t agenda) {
    return faction1 >= 0 && faction2 >= 0
        && Factions[faction1].diplo_agenda[faction2] & agenda;
}

bool want_revenge(int faction1, int faction2) {
    return Factions[faction1].diplo_status[faction2] & (DIPLO_ATROCITY_VICTIM | DIPLO_WANT_REVENGE);
}

bool allow_expand(int faction) {
    int bases = 0;
    if (*game_rules & RULES_SCN_NO_COLONY_PODS || !has_wmode(faction, WMODE_COLONIST)
    || *total_num_bases >= MaxBaseNum * 19 / 20) {
        return false;
    }
    for (int i=1; i < MaxPlayerNum && conf.expansion_autoscale > 0; i++) {
        if (is_human(i)) {
            bases = Factions[i].base_count;
            break;
        }
    }
    if (conf.expansion_limit > 0) {
        return Factions[faction].base_count < max(bases, conf.expansion_limit);
    }
    return true;
}

bool has_transport(int x, int y, int faction) {
    assert(valid_player(faction));
    for (int i = 0; i < *total_num_vehicles; i++) {
        VEH* veh = &Vehicles[i];
        if (veh->faction_id == faction && veh->x == x && veh->y == y
        && veh->is_transport()) {
            return true;
        }
    }
    return false;
}

bool has_defenders(int x, int y, int faction) {
    assert(valid_player(faction));
    for (int i = 0; i < *total_num_vehicles; i++) {
        VEH* veh = &Vehicles[i];
        if (veh->faction_id == faction && veh->x == x && veh->y == y
        && (veh->is_combat_unit() || veh->is_armored())
        && veh->triad() == TRIAD_LAND) {
            return true;
        }
    }
    return false;
}

bool has_colony_pods(int faction) {
    for (int i = 0; i < *total_num_vehicles; i++) {
        VEH* veh = &Vehicles[i];
        if (veh->faction_id == faction && veh->is_colony()) {
            return true;
        }
    }
    return false;
}

int find_hq(int faction) {
    for(int i=0; i < *total_num_bases; i++) {
        BASE* base = &Bases[i];
        if (base->faction_id == faction && has_fac_built(FAC_HEADQUARTERS, i)) {
            return i;
        }
    }
    return -1;
}

int manifold_nexus_owner() {
    for (int y=0; y < *map_axis_y; y++) {
        for (int x=y&1; x < *map_axis_x; x += 2) {
            MAP* sq = mapsq(x, y);
            /* First Manifold Nexus tile must also be visible to the owner. */
            if (sq && sq->landmarks & LM_NEXUS && sq->art_ref_id == 0) {
                return (sq->owner >= 0 && sq->is_visible(sq->owner) ? sq->owner : -1);
            }
        }
    }
    return -1;
}

int faction_might(int faction) {
    Faction* f = &Factions[faction];
    return plans[faction].mil_strength + 4*f->pop_total;
}

void __cdecl set_treaty(int faction1, int faction2, uint32_t treaty, bool add) {
    if (add) {
        Factions[faction1].diplo_status[faction2] |= treaty;
        if (treaty & DIPLO_UNK_40) {
            Factions[faction1].diplo_merc[faction2] = 50;
        }
        if (treaty & DIPLO_HAVE_INFILTRATOR && conf.counter_espionage) {
            int turns = probe_active_turns(faction1, faction2);
            MFactions[faction1].thinker_probe_end_turn[faction2] = *current_turn + turns;
            Factions[faction1].diplo_status[faction2] |= DIPLO_RENEW_INFILTRATOR;
            if (faction1 == MapWin->cOwner) {
                ParseNumTable[0] = turns;
                popp("modmenu", "SPYRENEW", 0, "infil_sm.pcx", 0);
            }
        }
    } else {
        Factions[faction1].diplo_status[faction2] &= ~treaty;
    }
}

void __cdecl set_agenda(int faction1, int faction2, uint32_t agenda, bool add) {
    if (add) {
        Factions[faction1].diplo_agenda[faction2] |= agenda;
    } else {
        Factions[faction1].diplo_agenda[faction2] &= ~agenda;
    }
}

int __cdecl mod_setup_player(int faction, int a2, int a3) {
    MFaction* m = &MFactions[faction];
    debug("setup_player %d %d %d\n", faction, a2, a3);
    if (!faction) {
        return setup_player(faction, a2, a3);
    }
    /*
    Fix issue with randomized faction agendas where they might be given agendas
    that are their opposition social models.
    */
    if (*game_state & STATE_RAND_FAC_LEADER_SOCIAL_AGENDA && !*current_turn) {
        int active_factions = 0;
        for (int i = 0; i < *total_num_vehicles; i++) {
            active_factions |= (1 << Vehs[i].faction_id);
        }
        for (int i = 0; i < 1000; i++) {
            int sfield = random(3);
            int smodel = random(3) + 1;
            if (sfield == m->soc_opposition_category && smodel == m->soc_opposition_model) {
                continue;
            }
            for (int j = 1; j < MaxPlayerNum; j++) {
                if (faction != j && (1 << j) & active_factions) {
                    if (MFactions[j].soc_priority_category == sfield
                    && MFactions[j].soc_priority_model == smodel) {
                        continue;
                    }
                }
            }
            m->soc_priority_category = sfield;
            m->soc_priority_model = smodel;
            debug("setup_player_agenda %s %d %d\n", m->filename, sfield, smodel);
            break;
        }
    }
    if (*game_state & STATE_RAND_FAC_LEADER_PERSONALITIES && !*current_turn) {
        m->AI_fight = random(3) - 1;
        m->AI_tech = 0;
        m->AI_power = 0;
        m->AI_growth = 0;
        m->AI_wealth = 0;

        for (int i = 0; i < 2; i++) {
            int val = random(4);
            switch (val) {
                case 0: m->AI_tech = 1; break;
                case 1: m->AI_power = 1; break;
                case 2: m->AI_growth = 1; break;
                case 3: m->AI_wealth = 1; break;
            }
        }
    }
    setup_player(faction, a2, a3);

    if (!is_human(faction) || conf.player_free_units > 0) {
        for (int i = 0; i < *total_num_vehicles; i++) {
            VEH* veh = &Vehicles[i];
            if (veh->faction_id == faction) {
                MAP* sq = mapsq(veh->x, veh->y);
                int former = (is_ocean(sq) ? BSC_SEA_FORMERS : BSC_FORMERS);
                int colony = (is_ocean(sq) ? BSC_SEA_ESCAPE_POD : BSC_COLONY_POD);
                for (int j = 0; j < conf.free_formers; j++) {
                    mod_veh_init(former, faction, veh->x, veh->y);
                }
                for (int j = 0; j < conf.free_colony_pods; j++) {
                    mod_veh_init(colony, faction, veh->x, veh->y);
                }
                break;
            }
        }
        Factions[faction].satellites_nutrient = conf.satellites_nutrient;
        Factions[faction].satellites_mineral = conf.satellites_mineral;
        Factions[faction].satellites_energy = conf.satellites_energy;
    }
    return 0;
}

/*
Improved social engineering AI choices feature.
*/
int social_score(int faction, int sf, int sm, int range, bool pop_boom, bool has_nexus,
int robust, int immunity, int impunity, int penalty) {
    enum {ECO, EFF, SUP, TAL, MOR, POL, GRW, PLA, PRO, IND, RES};
    Faction* f = &Factions[faction];
    MFaction* m = &MFactions[faction];
    double base_ratio = min(1.0, f->base_count / min(40.0, *map_area_sq_root * 0.5));
    int w_morale = (has_project(FAC_COMMAND_NEXUS, faction) ? 2 : 0)
        + (has_project(FAC_CYBORG_FACTORY, faction) ? 2 : 0);
    int w_probe = (range < 25 && *current_turn - m->thinker_last_mc_turn < 8 ? 5 : 0);
    int sc = 0;
    int vals[11];

    if ((&f->SE_Politics)[sf] == sm) {
        /* Evaluate the current active social model. */
        memcpy(vals, &f->SE_economy, sizeof(vals));
    } else {
        /* Take the faction base social values and apply all modifiers. */
        memcpy(vals, &f->SE_economy_base, sizeof(vals));

        for (int i=0; i<4; i++) {
            int j = (sf == i ? sm : (&f->SE_Politics)[i]);
            for (int k=0; k<11; k++) {
                int val = Social[i].effects[j][k];
                if ((1 << (i*4 + j)) & impunity) {
                    val = max(0, val);
                } else if ((1 << (i*4 + j)) & penalty) {
                    val = val * (val < 0 ? 2 : 1);
                }
                vals[k] += val;
            }
        }
        if (has_project(FAC_ASCETIC_VIRTUES, faction)) {
            vals[POL] += 1;
        }
        if (has_project(FAC_LIVING_REFINERY, faction)) {
            vals[SUP] += 2;
        }
        if (has_nexus) {
            if (is_alien(faction)) {
                vals[RES]++;
            }
            vals[PLA]++;
        }
        for (int k=0; k<11; k++) {
            if ((1 << k) & immunity) {
                vals[k] = max(0, vals[k]);
            } else if ((1 << k) & robust && vals[k] < 0) {
                vals[k] /= 2;
            }
        }
    }
    if (m->soc_priority_category >= 0 && m->soc_priority_model >= 0) {
        if (sf == m->soc_priority_category) {
            if (sm == m->soc_priority_model) {
                sc += conf.social_ai_bias;
            } else if (sm != SOCIAL_M_FRONTIER) {
                sc -= conf.social_ai_bias;
            }
        } else {
            if ((&f->SE_Politics)[m->soc_priority_category] == m->soc_priority_model) {
                sc += conf.social_ai_bias;
            } else if ((&f->SE_Politics)[m->soc_priority_category] != SOCIAL_M_FRONTIER) {
                sc -= conf.social_ai_bias;
            }
        }
    }
    if (vals[ECO] >= 2) {
        sc += (vals[ECO] >= 4 ? 16 : 12);
    }
    if (vals[EFF] < -2) {
        sc -= (vals[EFF] < -3 ? 20 : 14);
    }
    if (vals[SUP] < -3) {
        sc -= 10;
    }
    if (vals[SUP] < 0) {
        sc -= (int)((1.0 - base_ratio) * 10.0);
    }
    if (vals[MOR] >= 1 && vals[MOR] + w_morale >= 4) {
        sc += 10;
    }
    if (vals[PRO] >= 3 && !has_project(FAC_HUNTER_SEEKER_ALGO, faction)) {
        sc += 4 * max(0, 4 - range/8);
    }
    sc += max(2, 2 + 4*f->AI_wealth + 3*f->AI_tech - f->AI_fight)
        * clamp(vals[ECO], -3, 5);
    sc += max(2, 2*(f->AI_wealth + f->AI_tech) - f->AI_fight + (int)(4*base_ratio))
        * (min(6, vals[EFF]) + (vals[EFF] >= 3 ? 2 : 0));
    sc += max(3, 3 + 2*f->AI_power + 2*f->AI_fight)
        * clamp(vals[SUP], -4, 3);
    sc += max(2, 4 - range/8 + 2*f->AI_power + 2*f->AI_fight)
        * clamp(vals[MOR], -4, 4);

    if (!has_project(FAC_TELEPATHIC_MATRIX, faction)) {
        sc += (vals[POL] < 0 ? 2 : 4) * clamp(vals[POL], -5, 3);
        if (vals[POL] < -2) {
            sc -= (vals[POL] < -3 ? 4 : 2) * max(0, 4 - range/8)
                * (has_aircraft(faction) ? 2 : 1);
        }
        if (has_project(FAC_LONGEVITY_VACCINE, faction) && sf == SOCIAL_C_ECONOMICS) {
            sc += (sm == SOCIAL_M_PLANNED ? 10 : 0);
            sc += (sm == SOCIAL_M_SIMPLE || sm == SOCIAL_M_GREEN ? 5 : 0);
        }
        sc += 3*clamp(vals[TAL], -5, 5);

        int drone_score = 3 + (m->rule_drone > 0) - (m->rule_talent > 0)
            - (has_tech(Facility[FAC_PUNISHMENT_SPHERE].preq_tech, faction) ? 1 : 0);
        if (*SunspotDuration > 5 && *diff_level >= DIFF_LIBRARIAN
        && un_charter() && vals[POL] >= 0) {
            sc += 3*drone_score;
        }
        if (!un_charter() && vals[POL] >= 0) {
            sc += 2*drone_score;
        }
    }
    if (!has_project(FAC_CLONING_VATS, faction)) {
        if (pop_boom && vals[GRW] >= 4) {
            sc += 20;
        }
        if (vals[GRW] < -2) {
            sc -= 10;
        }
        sc += (pop_boom ? 6 : 3) * clamp(vals[GRW], -3, 6);
    }
    // Negative planet values reduce fungus yield
    if (plans[faction].keep_fungus) {
        sc += 3*clamp(vals[PLA], -3, 0);
    }
    sc += max(2, (f->SE_planet_base > 0 ? 5 : 2) + m->rule_psi/10
        + (has_project(FAC_MANIFOLD_HARMONICS, faction) ? 6 : 0)) * clamp(vals[PLA], -3, 3);
    sc += max(2, 5 - range/8 + w_probe + 2*f->AI_power + 2*f->AI_fight)
        * clamp(vals[PRO], -2, 3);
    sc += 8 * clamp(vals[IND], -3, 8 - *diff_level);

    if (~*game_rules & RULES_SCN_NO_TECH_ADVANCES) {
        sc += max(2, 3 + 4*f->AI_tech + 2*(f->AI_wealth - f->AI_fight))
            * clamp(vals[RES], -5, 5);
    }

    debug("social_score %d %d %d %d %s\n", faction, sf, sm, sc, Social[sf].soc_name[sm]);
    return sc;
}

int __cdecl SocialWin_social_ai(int faction,
int UNUSED(a2), int UNUSED(a3), int UNUSED(a4), int UNUSED(a5), int UNUSED(a6))
{
    Faction* f = &Factions[faction];
    if (f->SE_upheaval_cost_paid > 0) {
        social_set(faction);
    }
    return 0;
}

int __cdecl mod_social_ai(int faction, int a2, int a3, int a4, int a5, int a6) {
    Faction* f = &Factions[faction];
    MFaction* m = &MFactions[faction];
    bool pop_boom = 0;
    int want_pop = 0;
    int pop_total = 0;
    int robust = 0;
    int immunity = 0;
    int impunity = 0;
    int penalty = 0;

    if (is_human(faction) || !is_alive(faction)) {
        return 0;
    }
    if (!thinker_enabled(faction)) {
        return social_ai(faction, a2, a3, a4, a5, a6);
    }
    if (f->SE_upheaval_cost_paid > 0) {
        social_set(faction);
        return 0;
    }
    int range = (int)(plans[faction].enemy_base_range / (1.0 + 0.1 * min(4, plans[faction].enemy_bases)));
    bool has_nexus = (manifold_nexus_owner() == faction);
    assert(!memcmp(&f->SE_Politics, &f->SE_Politics_pending, 16));

    for (int i=0; i<m->faction_bonus_count; i++) {
        if (m->faction_bonus_id[i] == FCB_ROBUST) {
            robust |= (1 << m->faction_bonus_val1[i]);
        }
        if (m->faction_bonus_id[i] == FCB_IMMUNITY) {
            immunity |= (1 << m->faction_bonus_val1[i]);
        }
        if (m->faction_bonus_id[i] == FCB_IMPUNITY) {
            impunity |= (1 << (m->faction_bonus_val1[i] * 4 + m->faction_bonus_val2[i]));
        }
        if (m->faction_bonus_id[i] == FCB_PENALTY) {
            penalty |= (1 << (m->faction_bonus_val1[i] * 4 + m->faction_bonus_val2[i]));
        }
    }
    if (has_project(FAC_NETWORK_BACKBONE, faction)) {
        /* Cybernetic */
        impunity |= (1 << (4*SOCIAL_C_FUTURE + SOCIAL_M_CYBERNETIC));
    }
    if (has_project(FAC_CLONING_VATS, faction)) {
        /* Power & Thought Control */
        impunity |= (1 << (4*SOCIAL_C_VALUES + SOCIAL_M_POWER))
            | (1 << (4*SOCIAL_C_FUTURE + SOCIAL_M_THOUGHT_CONTROL));

    } else if (has_tech(Facility[FAC_CHILDREN_CRECHE].preq_tech, faction)) {
        for (int i=0; i<*total_num_bases; i++) {
            BASE* b = &Bases[i];
            if (b->faction_id == faction) {
                want_pop += (pop_goal(i) - b->pop_size)
                    * (b->nutrient_surplus > 1 && has_facility(FAC_CHILDREN_CRECHE, i) ? 4 : 1);
                pop_total += b->pop_size;
            }
        }
        if (pop_total > 0) {
            pop_boom = ((f->SE_growth < 4 ? 1 : 2) * want_pop) >= pop_total;
        }
    }
    debug("social_params %d %d %8s range: %2d has_nexus: %d pop_boom: %d want_pop: %3d pop_total: %3d "\
        "robust: %04x immunity: %04x impunity: %04x penalty: %04x\n", *current_turn, faction, m->filename,
        range, has_nexus, pop_boom, want_pop, pop_total, robust, immunity, impunity, penalty);
    int score_diff = 1 + (*current_turn + 11*faction) % 6;
    int sf = -1;
    int sm2 = -1;

    for (int i=0; i<4; i++) {
        int sm1 = (&f->SE_Politics)[i];
        int sc1 = social_score(faction, i, sm1, range, pop_boom, has_nexus, robust, immunity, impunity, penalty);

        for (int j=0; j<4; j++) {
            if (j == sm1 || !has_tech(Social[i].soc_preq_tech[j], faction) ||
            (i == m->soc_opposition_category && j == m->soc_opposition_model)) {
                continue;
            }
            int sc2 = social_score(faction, i, j, range, pop_boom, has_nexus, robust, immunity, impunity, penalty);
            if (sc2 - sc1 > score_diff) {
                sf = i;
                sm2 = j;
                score_diff = sc2 - sc1;
            }
        }
    }
    int cost = (is_alien(faction) ? 36 : 24);
    if (sf >= 0 && f->energy_credits > cost) {
        int sm1 = (&f->SE_Politics)[sf];
        (&f->SE_Politics_pending)[sf] = sm2;
        f->energy_credits -= cost;
        f->SE_upheaval_cost_paid += cost;
        debug("social_change %d %d %8s cost: %2d score_diff: %2d %s -> %s\n",
            *current_turn, faction, m->filename,
            cost, score_diff, Social[sf].soc_name[sm1], Social[sf].soc_name[sm2]);
    }
    social_set(faction);
    consider_designs(faction);
    return 0;
}

