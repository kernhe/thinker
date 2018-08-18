#ifndef __TERRANX_TYPES_H__
#define __TERRANX_TYPES_H__

typedef unsigned char byte;

#pragma pack(push, 1)
struct BASE
{
    short x_coord;
    short y_coord;
    char faction_id;
    char faction_id_former;
    char pop_size;
    char assimilation_turns_left;
    char nerve_staple_turns_left;
    char ai_plan_status;
    char factions_spotted_flags;
    char factions_pop_size_intel[8];
    char name[25];
    short unk_x_coord;
    short unk_y_coord;
    int status_flags;
    int event_flags;
    int governor_flags;
    int nutrients_accumulated;
    int minerals_accumulated;
    int production_id_last;
    int eco_damage;
    int queue_size;
    int queue_production_id[10];
    int resource_squares_flags;
    int specialist_total;
    int pad3;
    int pad4;
    int pad5;
    char facilities_built[12];
    int mineral_surplus_final;
    int minerals_accumulated_2;
    int pad6;
    int pad7;
    int pad8;
    int pad9;
    int nutrient_intake_1;
    int mineral_intake_1;
    int energy_intake_1;
    int unused_intake_1;
    int nutrient_intake_2;
    int mineral_intake_2;
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
    int unk10;
    short autoforward_land_base_id;
    short autoforward_sea_base_id;
    short autoforward_air_base_id;
    short pad10;
    int talent_total;
    int drone_total;
    int superdrone_total;
    int random_event_turns;
    int nerve_staple_count;
    int pad11;
    int pad12;
};

struct UNIT
{
    char name[32];
    int ability_flags;
    char chassis_type;
    char weapon_type;
    char armor_type;
    char reactor_type;
    char carry_capacity;
    char cost;
    char weapon_mode;
    char unit_plan;
    char factions_retired;
    char factions;
    char icon_offset;
    char unk1;
    short unk2_flags;
    short tech_preq_id;
};

struct VEH
{
    short x_coord;
    short y_coord;
    int flags_1;
    short flags_2;
    short proto_id;
    short unk1;
    char faction_id;
    char year_end_lurking;
    char damage_taken;
    char move_status;
    char waypoint_count;
    char patrol_current_point;
    short waypoint_1_x_coord;
    short waypoint_2_x_coord;
    short waypoint_3_x_coord;
    short waypoint_4_x_coord;
    short waypoint_1_y_coord;
    short waypoint_2_y_coord;
    short waypoint_3_y_coord;
    short waypoint_4_y_coord;
    char morale;
    char terraforming_turns;
    char type_crawling;
    char unk4;
    char road_moves_spent;
    char unk5;
    char unk6;
    char target_action;
    char unk8;
    char unk9;
    short home_base_id;
    short next_unit_id_stack;
    short prev_unit_id_stack;
};

struct MAP
{
    byte level;
    byte altitude;
    short flags;
    byte visibility;
    byte rocks;
    byte unk_1;
    char owner;
    int built_items;
    short landmarks;
    char unk_2;
    char art_ref_id;
    char pad[28];
};

struct FactMeta
{
    int is_leader_female;
    char filename[24];
    char search_key[24];
    char name_leader[24];
    char title_leader[24];
    char adj_leader[128];
    char adj_insult_leader[128];
    char adj_faction[128];
    char adj_insult_faction[128];
    char pad_1[128];
    char noun_faction[24];
    int noun_gender;
    int is_noun_plural;
    char adj_name_faction[128];
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
};

struct Faction
{
    int diplo_flags;
    int ranking;
    int diff_level;
    int unk_0;
    int unk_1;
    int tutorial_more_bases;
    int diplo_status[8];
    int diplo_agenda[8];
    int diplo_friction_1[8];
    int diplo_turn_check[8];
    int diplo_treaty_turns[8];
    char diplo_friction_2[8];
    int sanction_turns;
    int loan_years[8];
    int loan_payment[8];
    char gap_104[32];
    int minor_atrocities;
    int global_reputation;
    int diplo_unk1[8];
    int diplo_unk2[8];
    int diplo_backstabs[8];
    int diplo_unk3[8];
    int diplo_unk4[8];
    int map_trade_done;
    int governor_def_flags;
    int unk_2;
    int unk_3;
    int probe_count1;
    int probe_count2;
    char unk_4[28];
    int probe_count3;
    char unk_5[28];
    int energy_credits;
    int energy_cost;
    int SE_POLITICS_pending;
    int SE_ECONOMICS_pending;
    char gap_230[24];
    int SE_upheaval_cost_paid;
    int SE_economy_pending;
    int SE_effiency_pending;
    int SE_support_pending;
    int SE_talent_pending;
    int SE_morale_pending;
    int SE_police_pending;
    int SE_growth_pending;
    int SE_planet_pending;
    int SE_probe_pending;
    int SE_industy_pending;
    int SE_research_pending;
    char gap_278[8];
    char SE_support;
    char gap_281[7];
    char SE_morale;
    char gap_289[3];
    char SE_police;
    char gap_28D[3];
    char SE_growth;
    char gap_291[3];
    int SE_planet;
    int SE_probe;
    char gap_29C[12];
    int unk_6;
    char gap_2AC[36];
    int unk_7;
    char unk_8;
    char gap_2D5[11];
    int unk_9;
    char gap_2E4[8];
    int unk_10;
    int unk_11;
    char unk_12[4];
    int SE_base_research;
    int unk_13;
    int unk_14;
    int unk_15;
    int unk_16;
    int unk_17;
    int unk_18;
    int unk_19;
    int unk_20;
    int unk_21;
    int unk_22;
    int unk_23;
    int unk_24;
    int unk_25;
    char gap_330[44];
    int tech_ranking;
    int unk_26;
    int ODP_deployed;
    int theory_of_everything;
    char unk_27;
    char gap_36D[91];
    int tech_accumulated;
    int tech_researching_id;
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
    int unk_28;
    int council_call_turn;
    int unk_29[11];
    int unk_30[11];
    int unk_31;
    int unk_32;
    char unk_33;
    char unk_34;
    char gap_462[2];
    int unk_35;
    int unk_36;
    int unk_37;
    char gap_470[192];
    int saved_queue_size[8];
    int saved_queue_items[78];
    int unk_38;
    char unk_39[4];
    int unk_40;
    char unk_41[12];
    int unk_42;
    char unk_43[12];
    int unk_44;
    char gap_6B4[80];
    int unk_45;
    char gap_708[200];
    int unk_46;
    char gap_7D4[32];
    int unk_47;
    int unk_48;
    int unk_49;
    int unk_50;
    int labs_total;
    int satellites_nutrient;
    int satellites_mineral;
    int satellites_energy;
    int satellites_ODP;
    int best_weapon_value;
    int unk_55;
    int unk_56;
    int best_armor_value;
    int unk_58;
    int unk_59;
    int unk_60;
    int unk_61;
    int unk_62;
    int unk_63;
    int unk_64;
    int unk_65;
    int unk_66;
    int unk_67;
    int unk_68;
    char unk_69[4];
    char unk_70;
    char unk_71;
    char unk_72;
    char gap_85B[4];
    char unk_73;
    char gap_860[3];
    char unk_74;
    char unk_75;
    char unk_76;
    char unk_77;
    char unk_78;
    char gap_868[5];
    char unk_79;
    char gap_86E[490];
    char unk_80[512];
    short unk_81[512];
    int total_mil_units;
    int current_num_bases;
    int mil_strength_1;
    int mil_strength_2;
    int pop_total;
    int total_sea_units;
    int planet_busters;
    int probe_teams;
    int strategy_flags_1;
    short unk_82[128];
    char unk_83[128];
    char unk_84[128];
    short unk_85[128];
    short unk_86[128];
    short unk_87[128];
    short unk_88[128];
    short unk_89[128];
    short unk_90[128];
    char unk_91[128];
    char unk_92[128];
    char strategy_flags_2[128];
    short goals_unk1;
    short goals_unk2;
    int goals_x;
    int goals_y;
    int goals_flag;
    char gap_1A0C[1184];
    short goal_unk1;
    short goal_unk2;
    int goal_unk3;
    int goal_unk4;
    char gap_1EB8[388];
    int unk_93;
    int unk_94;
    int unk_95;
    int unk_96;
    int unk_97;
    int unk_98;
    int unk_99;
    char gap_2058[4];
    int unk_100[8];
    int corner_market_turn;
    int corner_market_active;
    int unk_101;
    int unk_102;
    int unk_103;
    int unk_104;
    int unk_105;
    int unk_106;
    int unk_107;
    int unk_108;
    int unk_109;
    int unk_110;
    char unk_111[4];
    int unk_112;
    int unk_113;
    int unk_114;
    int unk_115;
    int unk_116;
    int unk_117;
    int unk_118;
};

struct R_Basic
{
    int mov_rate_along_roads;
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
    char gap_68[8];
    int psi_combat_land_denominator;
    char gap_74[8];
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

struct R_Facility
{
    char* name;
    char* effect;
    int pad;
    int cost;
    int maint;
    int preq;
    int free;
    int AI_fight;
    int AI_growth;
    int AI_tech;
    int AI_wealth;
    int AI_power;
};

struct R_Tech
{
    int flags;
    char* name;
    int unk_0;
    int unk_1;
    int unk_2;
    int AI_growth;
    int AI_tech;
    int AI_wealth;
    int AI_power;
    int preq_tech1;
    int preq_tech2;
};

struct R_Ability
{
    char* name;
    char* description;
    char* abbreviation;
    int cost;
    int padding;
    int flags;
    int preq_tech;
};

struct R_Chassis
{
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

struct R_Citizen
{
    char* singular_name;
    char* plural_name;
    int preq_tech;
    int obsol_tech;
    int ops_bonus;
    int psych_bonus;
    int research_bonus;
};

struct R_Defense
{
    char* name;
    char* name_short;
    char defense_value;
    char mode;
    char cost;
    char padding1;
    short preq_tech;
    short padding2;
};

struct R_Reactor
{
    char* name;
    char* name_short;
    short preq_tech;
    short padding;
};

struct R_Terraform
{
    char* name;
    char* name_sea;
    int preq_tech;
    int preq_tech_sea;
    int flag;
    int flag_sea;
    int rate;
    char* shortcuts;
};

struct R_Weapon
{
    char* name;
    char* name_short;
    char offense_value;
    char icon;
    char mode;
    char cost;
    short preq_tech;
    short padding;
};

#pragma pack(pop)

#endif // __TERRANX_TYPES_H__
