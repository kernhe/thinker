#pragma once
#pragma pack(push, 1)

struct CChassis;
extern CChassis* Chassis;
struct CWeapon;
extern CWeapon* Weapon;
struct CArmor;
extern CArmor* Armor;
struct UNIT;
extern UNIT* Units;
struct VEH;
extern VEH* Vehicles;

struct BASE {
    short x;
    short y;
    char faction_id;
    char faction_id_former;
    char pop_size;
    char assimilation_turns_left;
    char nerve_staple_turns_left;
    char ai_plan_status;
    byte visibility;
    char factions_pop_size_intel[8];
    char name[25];
    short unk_x; // terraforming related
    short unk_y; // terraforming related
    int state_flags;
    int event_flags;
    int governor_flags;
    int nutrients_accumulated;
    int minerals_accumulated;
    int production_id_last;
    int eco_damage;
    int queue_size;
    int queue_items[10];
    int worked_tiles;
    int specialist_total;
    int specialist_unk_1;
    /*
    Specialist types (CCitizen, 4 bits per id) for the first 16 specialists in the base.
    These are assigned in base_yield and base_energy and chosen by best_specialist.
    */
    int specialist_types[2];
    char facilities_built[12];
    int mineral_surplus_final;
    int minerals_accumulated_2;
    int pad_1;
    int pad_2;
    int pad_3;
    int pad_4;
    int nutrient_intake;
    int mineral_intake; // Before multiplier facilities
    int energy_intake;
    int unused_intake;
    int nutrient_intake_2;
    int mineral_intake_2; // After multiplier facilities
    int energy_intake_2;
    int unused_intake_2;
    int nutrient_surplus;
    int mineral_surplus;
    int energy_surplus;
    int unused_surplus;
    int nutrient_inefficiency;
    int mineral_inefficiency;
    int energy_inefficiency;
    int unused_inefficiency;
    int nutrient_consumption;
    int mineral_consumption;
    int energy_consumption;
    int unused_consumption;
    int economy_total;
    int psych_total;
    int labs_total;
    int unk_5;
    short autoforward_land_base_id;
    short autoforward_sea_base_id;
    short autoforward_air_base_id;
    short defend_goal; // Thinker variable
    int talent_total;
    int drone_total;
    int superdrone_total;
    int random_event_turns;
    int nerve_staple_count;
    int pad_7;
    int pad_8;

    int item() {
        return queue_items[0];
    }
    bool item_is_project() {
        return queue_items[0] <= -SP_ID_First;
    }
    bool item_is_unit() {
        return queue_items[0] >= 0;
    }
};

struct MAP {
    byte climate; // 000 00 000 | altitude (3 bit) ; rainfall (2 bit) ; temperature (3 bit)
    byte contour; // altitude details
    /*
    val2 & 0xF0:
    AI colonization priority returned by world_site()
    This is written to the map struct by site_set()
    0 = unknown/not available, 1..15 higher numbers indicate a better location.
    When AltGr+4 debug overlay is enabled, MapWin_gen_terrain_poly renders
    this number on land tiles where value > 0.
    val2 & 0xF:
    Faction ID of the unit occupying this tile. 0xF = unoccupied.
    Sometimes faction ID of a deleted unit persists on the tile.
    */
    byte val2;
    /*
    The game keeps track of disjoint land/water areas and assigns each of them an ID number
    which is used to index the [128] planning variable arrays in Faction struct.
    Valid ranges: 1-62 (land), 65-126 (sea).
    */
    byte region;
    byte visibility;
    byte val3; // 00 000 000 | rocky (2 bit); lock faction_id (3 bit); using faction_id (3 bit)
    byte unk_1; // flags? bitfield
    int8_t owner;
    uint32_t items;
    uint16_t landmarks;
    byte unk_2; // 0x40 = set_dirty()
    byte art_ref_id;
    uint32_t visible_items[7];

    bool is_visible(int faction) {
        return visibility & (1 << faction);
    }
    bool is_owned() {
        return owner > 0;
    }
    bool is_land_region() {
        return region < 63; // Skip pole tiles
    }
    bool is_pole_tile() {
        return region == 63 || region == 127;
    }
    bool is_base() {
        return items & BIT_BASE_IN_TILE;
    }
    bool is_airbase() {
        return items & (BIT_BASE_IN_TILE | BIT_AIRBASE);
    }
    bool is_base_radius() {
        return items & BIT_BASE_RADIUS;
    }
    bool is_base_or_bunker() {
        return items & (BIT_BUNKER | BIT_BASE_IN_TILE);
    }
    bool is_fungus() {
        return items & BIT_FUNGUS;
    }
    int alt_level() {
        return climate >> 5;
    }
    bool is_rocky() {
        return val3 & TILE_ROCKY && alt_level() >= ALT_SHORE_LINE;
    }
    bool is_rolling() {
        return val3 & TILE_ROLLING;
    }
    bool is_rainy() {
        return climate & TILE_RAINY;
    }
    bool is_moist() {
        return climate & TILE_MOIST;
    }
    bool is_rainy_or_moist() {
        return climate & (TILE_MOIST | TILE_RAINY);
    }
    bool veh_in_tile() {
        return items & BIT_VEH_IN_TILE;
    }
    int veh_owner() {
        if ((val2 & 0xf) == 0xf) {
            return -1; // No vehicles in this tile
        }
        return val2 & 0xf;
    }
};

struct Landmark {
    int x;
    int y;
    char name[32];
};

struct Continent {
    int32_t tile_count; // count of tiles in region
    int32_t open_terrain; // count of non-rocky, non-fungus tiles (only 1 movement point to travel)
    int32_t unk_3; // highest world_site value (0-15)
    int32_t pods; // current count of supply and unity pods in region
    int32_t unk_5; // padding?
    uint8_t sea_coasts[8]; // sea specific regions, connections to land regions? bitmask
};

struct MFaction {
    int is_leader_female;
    char filename[24];
    char search_key[24];
    char name_leader[24];
    char title_leader[24];
    char adj_leader[128];
    char adj_insult_leader[128];
    char adj_faction[128];
    char adj_insult_faction[128];
    /*
    Thinker-specific save game variables.
    */
    int16_t thinker_header;
    int8_t thinker_flags;
    int8_t thinker_tech_id;
    int32_t thinker_tech_cost;
    int32_t thinker_unused;
    int16_t thinker_probe_lost;
    int16_t thinker_last_mc_turn;
    int16_t thinker_probe_end_turn[8];
    char pad_1[96];
    /*
    End of block
    */
    char noun_faction[24];
    int noun_gender;
    int is_noun_plural;
    char adj_name_faction[128]; // drops 2nd entry on line (abbreviation value?)
    char formal_name_faction[40];
    char insult_leader[24];
    char desc_name_faction[24];
    char assistant_name[24];
    char scientist_name[24];
    char assistant_city[24];
    char pad_2[176];
    int rule_tech_selected;
    int rule_morale;
    int rule_research;
    int rule_drone;
    int rule_talent;
    int rule_energy;
    int rule_interest;
    int rule_population;
    int rule_hurry;
    int rule_techcost;
    int rule_psi;
    int rule_sharetech;
    int rule_commerce;
    int rule_flags;
    int faction_bonus_count;
    int faction_bonus_id[8];
    int faction_bonus_val1[8];
    int faction_bonus_val2[8];
    int AI_fight;
    int AI_growth;
    int AI_tech;
    int AI_wealth;
    int AI_power;
    int soc_priority_category;
    int soc_opposition_category;
    int soc_priority_model;
    int soc_opposition_model;
    int soc_priority_effect;
    int soc_opposition_effect;

    bool is_aquatic() {
        return rule_flags & RFLAG_AQUATIC;
    }
};

struct Goal {
    short type;
    short priority;
    int x;
    int y;
    int base_id;
};

struct Faction {
    int player_flags;
    int ranking; // 0 (lowest) to 7 (highest)
    int diff_level; // 3 for AIs, equal to diff_level setting for humans
    int base_name_offset; // Keep track which base names have been used
    int base_sea_name_offset; // Keep track which sea base names have been used
    int last_base_turn; // Turn for last built, captured or acquired (drone riot) base
    int diplo_status[8]; // Contains all formal treaties
    int diplo_agenda[8];
    int diplo_friction[8];
    int diplo_spoke[8]; // Turn for the last player-to-AI communication; -1 for never
    int diplo_merc[8]; // Possibly higher values indicate willingness for deal-making
    char diplo_patience[8]; // AI-to-player
    int sanction_turns; // Turns left for economic sanctions imposed by other factions for atrocities
    int loan_balance[8]; // Loan balance remaining this faction owes another to be paid over term
    int loan_payment[8]; // The per turn payment amount this faction owes another faction
    int unk_1[8]; // unused
    int integrity_blemishes;
    int diplo_reputation;
    int diplo_gifts[8]; // ? Gifts and bribes we have received
    int diplo_wrongs[8]; // Number of times we double crossed this faction
    int diplo_betrayed[8]; // Number of times double crossed by this faction
    int diplo_unk_3[8]; // ? combat related
    int diplo_unk_4[8]; // ? combat related
    int traded_maps; // bitfield of other factions that have traded maps with faction
    int base_governor_adv; // default advanced Governor settings
    int atrocities; // count committed by faction
    int major_atrocities; // count committed by faction
    int subvert_total; // ? probe: mind control base (+4) / subvert unit (+1) total
    int diplo_subvert[8]; // ? probe: mind control base (+4) / subvert unit (+1) per faction
    int diplo_stolen_techs[8]; // probe: successfully procured research data (tech/map) per faction
    int energy_credits;
    int energy_cost;
    int SE_Politics_pending;
    int SE_Economics_pending;
    int SE_Values_pending;
    int SE_Future_pending;
    int SE_Politics;
    int SE_Economics;
    int SE_Values;
    int SE_Future;
    int SE_upheaval_cost_paid;
    int SE_economy_pending;
    int SE_effic_pending;
    int SE_support_pending;
    int SE_talent_pending;
    int SE_morale_pending;
    int SE_police_pending;
    int SE_growth_pending;
    int SE_planet_pending;
    int SE_probe_pending;
    int SE_industry_pending;
    int SE_research_pending;
    int SE_economy;
    int SE_effic;
    int SE_support;
    int SE_talent;
    int SE_morale;
    int SE_police;
    int SE_growth;
    int SE_planet;
    int SE_probe;
    int SE_industry;
    int SE_research;
    int SE_economy_2;
    int SE_effic_2;
    int SE_support_2;
    int SE_talent_2;
    int SE_morale_2;
    int SE_police_2;
    int SE_growth_2;
    int SE_planet_2;
    int SE_probe_2;
    int SE_industry_2;
    int SE_research_2;
    int SE_economy_base;
    int SE_effic_base;
    int SE_support_base;
    int SE_talent_base;
    int SE_morale_base;
    int SE_police_base;
    int SE_growth_base;
    int SE_planet_base;
    int SE_probe_base;
    int SE_industry_base;
    int SE_research_base;
    int energy_surplus_total;
    int facility_maint_total;
    int tech_commerce_bonus; // Increases commerce income
    int turn_commerce_income;
    int unk_17;
    int unk_18;
    int tech_fungus_nutrient;
    int tech_fungus_mineral;
    int tech_fungus_energy;
    int unk_22;
    int SE_alloc_psych;
    int SE_alloc_labs;
    int unk_25;
    int unk_26[11]; // unused
    int tech_ranking; // Twice the number of techs discovered
    int unk_27;
    int ODP_deployed;
    int theory_of_everything;
    char tech_trade_source[92];
    int tech_accumulated;
    int tech_research_id;
    int tech_cost;
    int earned_techs_saved;
    int net_random_event;
    int AI_fight;
    int AI_growth;
    int AI_tech;
    int AI_wealth;
    int AI_power;
    int target_x;
    int target_y;
    int best_mineral_output; // For faction bases highest mineral_intake_2 + 2 * mineral_surplus
    int council_call_turn;
    int unk_29[11]; // Council related
    int unk_30[11]; // Council related
    byte facility_announced[4]; // bitfield - used to determine one time play of fac audio blurb
    int unk_32;
    int unk_33;
    int clean_minerals_modifier; // Starts from zero and increases by one after each fungal pop
    int base_id_attack_target; // Battle planning of base to attack, -1 if not set
    int unk_37;
    char saved_queue_name[8][24];
    int saved_queue_size[8];
    int saved_queue_items[8][10];
    int unk_40[8];
    int unk_41[40];
    int unk_42[32];
    int unk_43[8];
    int unk_44;
    int unk_45;
    int unk_46;
    int unk_47;
    int nutrient_surplus_total;
    int labs_total;
    int satellites_nutrient;
    int satellites_mineral;
    int satellites_energy;
    int satellites_ODP;
    int best_weapon_value;
    int best_psi_land_offense;
    int best_psi_land_defense;
    int best_armor_value;
    int best_land_speed;
    int enemy_best_weapon_value; // Enemy refers here to any non-pact faction
    int enemy_best_armor_value;
    int enemy_best_land_speed;
    int enemy_best_psi_land_offense;
    int enemy_best_psi_land_defense;
    int unk_64;
    int unk_65;
    int unk_66;
    int unk_67;
    int unk_68;
    int unk_69;
    byte units_active[512];
    byte units_queue[512];
    short units_lost[512];
    int total_combat_units;
    int base_count;
    int mil_strength_1;
    int mil_strength_2;
    int pop_total;
    int unk_70;
    int planet_busters;
    int unk_71;
    int unk_72;
    /*
    AI planning variables that relate to faction units in specific disjoint land/water areas.
    All of these are indexed by the region value in MAP struct.
    These are updated in enemy_strategy and mainly only used by the legacy vanilla AI.
    */
    short region_total_combat_units[128];
    byte region_total_bases[128];
    byte region_total_offensive_units[128];
    short region_force_rating[128]; // Combined offensive/morale rating of all units in the area
    short region_flags[128]; // Movement planning flags
    short region_territory_tiles[128];
    short region_visible_tiles[128];
    short region_good_tiles[128];
    short region_unk_5[128]; // Unknown reset_territory/enemy_move counter
    byte region_unk_6[128]; // Unknown enemy_strategy state
    byte region_territory_pods[128];
    byte region_base_plan[128]; // visible in map UI with omni view + debug mode under base name
    /* End of block */
    Goal goals[75];
    Goal sites[25];
    int unk_93;
    int unk_94;
    int unk_95;
    int unk_96;
    int unk_97;
    int tech_achieved; // count of technology faction has discovered/achieved
    int time_bonus_count; // Net MP: Each is worth amount in seconds under Time Controls Extra
    int unk_99; // unused?
    uint32_t secret_project_intel[8]; // Bitfield; News of SPs other factions are working on
    int corner_market_turn;
    int corner_market_active;
    int unk_101;
    int unk_102;
    int unk_103;
    int player_flags_ext;
    int unk_105;
    int unk_106;
    int unk_107;
    int unk_108;
    /*
    Thinker variables in the old save game format.
    */
    short old_thinker_header;
    char old_thinker_flags;
    char old_thinker_tech_id;
    int old_thinker_tech_cost;
    int unk_111;
    int unk_112;
    int unk_113;
    int unk_114;
    int unk_115;
    int unk_116;
    int unk_117;
    int unk_118;
};

struct CRules {
    int move_rate_roads;
    int nutrient_intake_req_citizen;
    int max_airdrop_rng_wo_orbital_insert;
    int artillery_max_rng;
    int artillery_dmg_numerator;
    int artillery_dmg_denominator;
    int nutrient_cost_multi;
    int mineral_cost_multi;
    int rules_tech_discovery_rate;
    int limit_mineral_inc_for_mine_wo_road;
    int nutrient_effect_mine_sq;
    int min_base_size_specialists;
    int drones_induced_genejack_factory;
    int pop_limit_wo_hab_complex;
    int pop_limit_wo_hab_dome;
    int tech_preq_improv_fungus;
    int tech_preq_ease_fungus_mov;
    int tech_preq_build_road_fungus;
    int tech_preq_allow_2_spec_abil;
    int tech_preq_allow_3_nutrients_sq;
    int tech_preq_allow_3_minerals_sq;
    int tech_preq_allow_3_energy_sq;
    int extra_cost_prototype_land;
    int extra_cost_prototype_sea;
    int extra_cost_prototype_air;
    int psi_combat_land_numerator;
    int psi_combat_sea_numerator;
    int psi_combat_air_numerator;
    int psi_combat_land_denominator;
    int psi_combat_sea_denominator;
    int psi_combat_air_denominator;
    int starting_energy_reserve;
    int combat_bonus_intrinsic_base_def;
    int combat_bonus_atk_road;
    int combat_bonus_atk_higher_elevation;
    int combat_penalty_atk_lwr_elevation;
    int tech_preq_orb_insert_wo_space;
    int min_turns_between_councils;
    int minerals_harvesting_forest;
    int territory_max_dist_base;
    int turns_corner_global_energy_market;
    int tech_preq_mining_platform_bonus;
    int tech_preq_economic_victory;
    int combat_penalty_atk_airdrop;
    int combat_bonus_fanatic;
    int combat_land_vs_sea_artillery;
    int combat_artillery_bonus_altitude;
    int combat_mobile_open_ground;
    int combat_mobile_def_in_rough;
    int combat_bonus_trance_vs_psi;
    int combat_bonus_empath_song_vs_psi;
    int combat_infantry_vs_base;
    int combat_penalty_air_supr_vs_ground;
    int combat_bonus_air_supr_vs_air;
    int combat_penalty_non_combat_vs_combat;
    int combat_comm_jammer_vs_mobile;
    int combat_bonus_vs_ship_port;
    int combat_AAA_bonus_vs_air;
    int combat_defend_sensor;
    int combat_psi_bonus_per_PLANET;
    int retool_strictness;
    int retool_penalty_prod_change;
    int retool_exemption;
    int tgl_probe_steal_tech;
    int tgl_humans_always_contact_tcp;
    int tgl_humans_always_contact_pbem;
    int max_dmg_percent_arty_base_bunker;
    int max_dmg_percent_arty_open;
    int max_dmg_percent_arty_sea;
    int freq_global_warming_numerator;
    int freq_global_warming_denominator;
    int normal_start_year;
    int normal_ending_year_lowest_3_diff;
    int normal_ending_year_highest_3_diff;
    int tgl_oblit_base_atrocity;
    int base_size_subspace_gen;
    int subspace_gen_req;
};

struct CResourceInfo {
    int ocean_sq_nutrient;
    int ocean_sq_mineral;
    int ocean_sq_energy;
    int pad_0;
    int base_sq_nutrient;
    int base_sq_mineral;
    int base_sq_energy;
    int pad_1;
    int bonus_sq_nutrient;
    int bonus_sq_mineral;
    int bonus_sq_energy;
    int pad_2;
    int forest_sq_nutrient;
    int forest_sq_mineral;
    int forest_sq_energy;
    int pad_3;
    int recycling_tanks_nutrient;
    int recycling_tanks_mineral;
    int recycling_tanks_energy;
    int pad_4;
    int improved_land_nutrient;
    int improved_land_mineral;
    int improved_land_energy;
    int pad_5;
    int improved_sea_nutrient;
    int improved_sea_mineral;
    int improved_sea_energy;
    int pad_6;
    int monolith_nutrient;
    int monolith_mineral;
    int monolith_energy;
    int pad_7;
    int borehole_sq_nutrient;
    int borehole_sq_mineral;
    int borehole_sq_energy;
    int pad_8;
};

struct CResourceName {
    char* name_singular;
    char* name_plural;
};

struct CEnergy {
    char* abbrev;
    char* name;
};

struct CFacility {
    char* name;
    char* effect;
    int pad;
    int cost;
    int maint;
    int preq_tech;
    int free;
    int AI_fight;
    int AI_growth;
    int AI_tech;
    int AI_wealth;
    int AI_power;
};

struct CTech {
    int flags;
    char* name;
    char short_name[12];
    int AI_growth;
    int AI_tech;
    int AI_wealth;
    int AI_power;
    int preq_tech1;
    int preq_tech2;
};

struct CCitizen {
    char* singular_name;
    char* plural_name;
    int preq_tech;
    int obsol_tech;
    int ops_bonus;
    int psych_bonus;
    int research_bonus;
};

struct CAbility {
    char* name;
    char* description;
    char* abbreviation;
    int cost;
    int unk_1;
    int flags;
    short preq_tech;
    short pad;
};

struct CChassis {
    char* offsv1_name;
    char* offsv2_name;
    char* offsv_name_lrg;
    char* defsv1_name;
    char* defsv2_name;
    char* defsv_name_lrg;
    int offsv1_gender;
    int offsv2_gender;
    int offsv_gender_lrg;
    int defsv1_gender;
    int defsv2_gender;
    int defsv_gender_lrg;
    int offsv1_is_plural;
    int offsv2_is_plural;
    int offsv_is_plural_lrg;
    int defsv1_is_plural;
    int defsv2_is_plural;
    int defsv_is_plural_lrg;
    char speed;
    char triad;
    char range;
    char cargo;
    char cost;
    char missile;
    char sprite_flag_x_coord[8];
    char sprite_flag_y_coord[8];
    char sprite_unk1_x_coord[8];
    char sprite_unk1_y_coord[8];
    char sprite_unk2_x_coord[8];
    char sprite_unk2_y_coord[8];
    char sprite_unk3_x_coord[8];
    char sprite_unk3_y_coord[8];
    short preq_tech;
};

struct CArmor {
    char* name;
    char* name_short;
    char defense_value;
    char mode;
    char cost;
    char padding1;
    short preq_tech;
    short padding2;
};

struct CReactor {
    char* name;
    char* name_short;
    short preq_tech;
    short padding;
};

struct CWeapon {
    char* name;
    char* name_short;
    char offense_value;
    char icon;
    char mode;
    char cost;
    short preq_tech;
    short padding;
};

struct CTerraform {
    char* name;
    char* name_sea;
    int preq_tech;
    int preq_tech_sea;
    uint32_t bit;
    uint32_t bit_incompatible;
    int rate;
    char* shortcuts;
};

struct CMorale {
    char* name;
    char* name_lifecycle;
};

struct CCombatMode {
    char* name;
    char* hyphened;
    char* abbrev;
    char* letter;
};

struct COrder {
    char* order;
    char* order_sea;
    char* letter;
};

struct CTimeControl {
    char* name;
    int turn;
    int base;
    int unit;
    int event;
    int extra;
    int refresh;
    int accumulated;
};

struct CSocialField {
    char* field_name;
    int   soc_preq_tech[4];
    char* soc_name[4];
    int   effects[4][11];
};

struct CSocialEffect {
    char set1[24];
    char set2[24];
    char padding[56];
};

struct CMight {
    char* adj_start;
    char* adj;
};

struct CBonusName {
    char key[24];
};

struct CProposal {
    char* name;
    char* description;
    int preq_tech;
};

struct CNatural {
    char* name;
    char* name_short;
};

struct CWorldbuilder {
    // Seeded land size of a standard world (allowed: 50 to 4000, default: 384)
    int land_base;
    // Additional land from LAND selection: x0, x1, x2 (allowed: 0 to 2000, default: 256)
    int land_mod;
    // Base size of a land mass seed (allowed: 5 to 1000, default: 12)
    int continent_base;
    // Increased size from LAND selection: x0, x1, x2 (allowed: 5 to 1000, default: 24)
    int continent_mod;
    // Base # of extra hills (allowed: 0 to 100, default: 1)
    int hills_base;
    // Additional hills from TIDAL selection: x0, x1, x2 (allowed: 0 to 100, default: 2)
    int hills_mod;
    // Basic plateau size (allowed: 0 to 500, default: 4)
    int plateau_base;
    // Plateau modifier based on LAND selection: x0, x1, x2 (allowed: 0 to 500, default: 8)
    int plateau_mod;
    // Basic # of rivers (allowed: 0 to 100, default: 8)
    int rivers_base;
    // Additional rivers based on RAIN selection (allowed: 0 to 100, default: 12)
    int rivers_rain_mod;
    // Latitude DIVISOR for temperature based on HEAT
    // Smaller # increases effect of HEAT selection (allowed: 1 to 64, default: 14)
    int solar_energy;
    // Latitude DIVISOR for thermal banding; Smaller # widens hot bands (allowed: 1 to 64, default: 14)
    int thermal_band;
    // Latitude DIVISOR for thermal deviance; Smaller # increases randomness (allowed: 1 to 64, default: 8)
    int thermal_deviance;
    // Latitude DIVISOR for global warming; Smaller # increases effect of warming (allowed: 1 to 64, default: 8)
    int global_warming;
    // Magnitude of sea level changes from ice cap melting/freezing (allowed: 1 to 100, default: 5)
    int sea_level_rises;
    // Size of cloud mass trapped by peaks (allowed: 0 to 20, default: 5)
    int cloudmass_peaks;
    // Size of cloud mass trapped by hills (allowed: 0 to 20, default: 3)
    int cloudmass_hills;
    // Multiplier for rainfall belts (allowed: 0 to 8, default: 1)
    int rainfall_coeff;
    // Encourages fractal to grow deep water (allowed: -100 to 100, default: 15)
    int deep_water;
    // Encourages fractal to grow shelf (allowed: -100 to 100, default: 10)
    int shelf;
    // Encourages highland plains (allowed: -100 to 100, default: 15)
    int plains;
    // Encourages wider beaches (allowed: -100 to 100, default: 10)
    int beach;
    // Encourages hills x TIDAL selection (allowed: 0 to 100, default: 10)
    int hills;
    // Encourages peaks (allowed: -100 to 100, default: 25)
    int peaks;
    // Fungus coefficient based on LIFE selection (allowed: 0 to 5, default: 1)
    int fungus;
    // Continent size ratios #1 (allowed: n/a, default: 3)
    int cont_size_ratio1;
    // Continent size ratios #2 (allowed: n/a, default: 6)
    int cont_size_ratio2;
    // Continent size ratios #3 (allowed: n/a, default: 12)
    int cont_size_ratio3;
    // Continent size ratios #4 (allowed: n/a, default: 18)
    int cont_size_ratio4;
    // Continent size ratios #5 (allowed: n/a, default: 24)
    int cont_size_ratio5;
    // Higher # increases island count (allowed: 1 to 500, default: 36)
    int islands;
};


#pragma pack(pop)

