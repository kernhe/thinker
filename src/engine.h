#pragma once

/* Temporarily disable warnings for thiscall parameter type. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"

#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <algorithm>
#include <set>
#include <list>
#include <string>
#include <vector>

typedef uint8_t byte;
typedef uint32_t Dib;
typedef struct char256 { char str[256]; } char256;

#include "engine_enums.h"
#include "engine_types.h"
#include "engine_veh.h"
#include "engine_win.h"

struct MapTile {
    int x;
    int y;
    MAP* sq;
};

struct Point {
    int x;
    int y;
};

struct PointComp {
    bool operator()(const Point& p1, const Point& p2) const
    {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    }
};

struct MapNode {
    int x;
    int y;
    int type;
};

struct NodeComp {
    bool operator()(const MapNode& p1, const MapNode& p2) const
    {
        return p1.x < p2.x || (p1.x == p2.x && (
            p1.y < p2.y || (p1.y == p2.y && (p1.type < p2.type))
        ));
    }
};

template <class T, class C>
bool has_item(const T& a, const C& b) {
    return std::find(a.begin(), a.end(), b) != a.end();
}

template <class T>
const T& min (const T& a, const T& b) {
    return std::min(a, b);
}

template <class T>
const T& max (const T& a, const T& b) {
    return std::max(a, b);
}

template <class T>
const T& clamp (const T& value, const T& low, const T& high) {
    return (value < low ? low : (value > high ? high : value));
}

typedef std::set<MapNode,NodeComp> NodeSet;
typedef std::set<Point,PointComp> Points;
typedef std::list<Point> PointList;
typedef std::set<std::string> set_str_t;
typedef std::vector<std::string> vec_str_t;

typedef int (__cdecl *fp_void)();
typedef int (__cdecl *fp_1int)(int);
typedef int (__cdecl *fp_2int)(int, int);
typedef int (__cdecl *fp_3int)(int, int, int);
typedef int (__cdecl *fp_4int)(int, int, int, int);
typedef int (__cdecl *fp_5int)(int, int, int, int, int);
typedef int (__cdecl *fp_6int)(int, int, int, int, int, int);
typedef int (__cdecl *fp_7int)(int, int, int, int, int, int, int);
typedef int (__cdecl *fp_8int)(int, int, int, int, int, int, int, int);

typedef int (__thiscall *tc_1int)(void*);
typedef int (__thiscall *tc_2int)(void*, int);
typedef int (__thiscall *tc_3int)(void*, int, int);
typedef int (__thiscall *tc_4int)(void*, int, int, int);
typedef int (__thiscall *tc_5int)(void*, int, int, int, int);
typedef int (__thiscall *tc_6int)(void*, int, int, int, int, int);
typedef int (__thiscall *tc_7int)(void*, int, int, int, int, int, int);
typedef int (__thiscall *tc_8int)(void*, int, int, int, int, int, int, int);

/*
pad_1 in MFaction is reserved for faction specific variables.
pad_2 in MFaction[0] is reserved for global game state.
*/
struct ThinkerData {
    uint64_t reserved;
    uint64_t game_time_spent;
    char build_date[12];
    uint32_t map_random_value;
    int8_t padding[144];
};

static_assert(sizeof(struct CRules) == 308, "");
static_assert(sizeof(struct CSocialField) == 212, "");
static_assert(sizeof(struct CFacility) == 48, "");
static_assert(sizeof(struct CTech) == 44, "");
static_assert(sizeof(struct MFaction) == 1436, "");
static_assert(sizeof(struct Faction) == 8396, "");
static_assert(sizeof(struct BASE) == 308, "");
static_assert(sizeof(struct UNIT) == 52, "");
static_assert(sizeof(struct VEH) == 52, "");
static_assert(sizeof(struct MAP) == 44, "");
static_assert(sizeof(struct ThinkerData) == 176, "");

/*
Thinker functions that are replacements to the SMACX binary versions
should be prefixed with 'mod_' if their equivalent is also listed here.
*/

extern const char** EngineVersion;
extern const char** EngineDate;
extern char*** TextLabels;
extern char* LastSavePath;
extern char* ScriptFile;
extern char* MapFilePath;
extern char* StrBuffer;
extern BASE** current_base_ptr;
extern int* current_base_id;
extern int* compute_base_id;
extern int* game_preferences;
extern int* game_more_preferences;
extern int* game_warnings;
extern int* game_state;
extern int* game_rules;
extern int* diff_level;
extern int* expansion_enabled;
extern int* multiplayer_active;
extern int* pbem_active;
extern int* human_players;
extern int* current_turn;
extern int* active_faction;
extern int* total_num_bases;
extern int* total_num_vehicles;
extern int* VehDropLiftVehID;
extern int* VehLiftX;
extern int* VehLiftY;
extern int* VehBitError;
extern int* VehBasicBattleMorale;
extern int* map_random_seed;
extern int* map_toggle_flat;
extern int* map_area_tiles;
extern int* map_area_sq_root;
extern int* map_axis_x;
extern int* map_axis_y;
extern int* map_half_x;
extern int* MapSizePlanet;
extern int* MapOceanCoverage;
extern int* MapLandCoverage;
extern int* MapErosiveForces;
extern int* MapPlanetaryOrbit;
extern int* MapCloudCover;
extern int* MapNativeLifeForms;
extern int* MapLandmarkCount;
extern int* AltNaturalDefault;
extern int* AltNatural;
extern int* ObjectiveReqVictory;
extern int* ObjectivesSuddenDeathVictory;
extern int* ObjectiveAchievePts;
extern int* VictoryAchieveBonusPts;
extern int* MissionYearCurrent;
extern int* StartingMissionYear;
extern int* EndingMissionYear;
extern int* TectonicDetonationCount;
extern int* SunspotDuration;
extern int* MountPlanetX;
extern int* MountPlanetY;
extern int* DustCloudDuration;
extern int* SunspotDuration;
extern int* GovernorFaction;
extern int* climate_future_change;
extern int* un_charter_repeals;
extern int* un_charter_reinstates;
extern int* gender_default;
extern int* plurality_default;
extern int* current_player_faction;
extern int* diplo_second_faction;
extern int* diplo_third_faction;
extern int* diplo_tech_faction;
extern int* reportwin_opponent_faction;
extern int* diplo_value_93FA98;
extern int* diplo_value_93FA24;
extern int* diplo_entry_id;
extern int* diplo_counter_proposal_id;
extern int* diplo_current_proposal_id;
extern int* diplo_ask_base_swap_id;
extern int* diplo_bid_base_swap_id;
extern int* diplo_tech_id1;
extern int* base_find_dist;
extern int* veh_attack_flags;
extern int* screen_width;
extern int* screen_height;
extern char256* ParseStrBuffer;
extern int* ParseNumTable;
extern int* ParseStrPlurality;
extern int* ParseStrGender;
extern int* DialogChoices;
extern int* GameHalted;
extern int* ControlTurnA;
extern int* ControlTurnB;
extern int* ControlTurnC;
extern int* ControlRedraw;
extern int* ControlUpkeepA;
extern int* ControlWaitLoop;
extern int* WorldAddTemperature;
extern int* WorldSkipTerritory;
extern int* WinModalState;
extern int* PopupDialogState;

extern uint8_t* TechOwners;
extern int* SecretProjects;
extern int* CostRatios;
extern uint8_t* FactionStatus;
extern int16_t (*FactionTurnMight)[8];
extern int* FactionRankings;
extern int* RankingFactionIDUnk1;
extern int* RankingFactionIDUnk2;
extern int* FactionRankingsUnk;
extern int* DiploFriction;
extern int* DiploFrictionFactionIDWith;
extern int* DiploFrictionFactionID;

extern ThinkerData* ThinkerVars;
extern MFaction* MFactions;
extern Faction* Factions;
extern BASE* Bases;
extern UNIT* Units;
extern VEH* Vehicles;
extern VEH* Vehs;
extern MAP** MapTiles;
extern Continent* Continents;
extern Landmark* Landmarks;
extern Console* MapWin;
extern Win* BaseWin;
extern Win* BattleWin;
extern Win* CouncilWin;
extern Win* DatalinkWin;
extern Win* DesignWin;
extern Win* DiploWin;
extern Win* FameWin;
extern Win* StringBox;
extern Win* InfoWin;
extern Win* BaseMapWin;
extern Win* MessageWin;
extern Win* MonuWin;
extern Win* MultiWin;
extern Win* NetWin;
extern Win* NetTechWin;
extern Win* PickWin;
extern Win* PlanWin;
extern Win* PrefWin;
extern Win* ReportWin;
extern Win* SocialWin;
extern Win* StatusWin;
extern Win* TutWin;
extern Win* WorldWin;
extern Font** MapLabelFont;
extern Sprite** FactionPortraits;
extern void* NetMsg;

// Rules parsed from alphax.txt
extern CRules* Rules;
extern CTech* Tech;
extern CFacility* Facility;
extern CAbility* Ability;
extern CChassis* Chassis;
extern CCitizen* Citizen;
extern CArmor* Armor;
extern CReactor* Reactor;
extern CResourceInfo* ResInfo;
extern CResourceName* ResName;
extern CEnergy* Energy;
extern CTerraform* Terraform;
extern CWeapon* Weapon;
extern CNatural* Natural;
extern CProposal* Proposal;
extern CWorldbuilder *WorldBuilder;
extern CMorale* Morale;
extern CCombatMode* DefenseMode;
extern CCombatMode* OffenseMode;
extern COrder* Order;
extern CTimeControl* TimeControl;
extern CSocialField* Social;
extern CSocialEffect* SocialEffect;
extern CMight* Might;
extern CBonusName* BonusName;
extern char** Mood;
extern char** Repute;


typedef int(__cdecl *Fbattle_fight_1)(int veh_id, int offset, bool use_table_offset, int v1, int v2);
typedef int(__cdecl *Fpropose_proto)(int faction_id, VehChassis chassis, VehWeapon weapon, VehArmor armor,
    int abilities, VehReactor reactor, VehPlan ai_plan, const char* name);
typedef int(__cdecl *Fact_airdrop)(int veh_id, int x, int y, int veh_attack_flags);
typedef int(__cdecl *Fact_destroy)(int veh_id, int flags, int x, int y);
typedef int(__cdecl *Fact_gate)(int veh_id, int base_id);
typedef int(__cdecl *Fhas_abil)(int unit_id, int ability_flag);
typedef int(__cdecl *Fparse_says)(int index, const char* text, int v1, int v2);
typedef int(__cdecl *Fhex_cost)(int unit_id, int faction_id, int x1, int y1, int x2, int y2, int a7);
typedef void(__cdecl *Fname_base)(int faction_id, char* name, bool save_offset, bool sea_base);
typedef int(__cdecl *Fveh_cost)(int item_id, int base_id, int* ptr);
typedef int (__cdecl *Fsave_daemon)(const char* filename);
typedef int(__cdecl *Fbase_at)(int x, int y);
typedef int(__cdecl *Fpopp)(const char* filename, const char* label, int v1,
    const char* pcx_filename, int v2);
typedef int (__cdecl *FX_pop)(const char* filename, const char* label, int a3, int a4, int a5, int a6);
typedef int (__cdecl *FX_pops)(const char* filename, const char* label,
    int a3, int a4, int a5, int a6, int a7, int a8, int a9);
typedef int(__cdecl *Fpop_ask_number)(const char *filename, const char* label, int value, int a4);
typedef int(__cdecl *Fname_proto)(char* name, int unit_id, int faction_id,
VehChassis chassis, VehWeapon weapon, VehArmor armor, VehAblFlag abls, VehReactor reactor);

typedef int(__thiscall *FMapWin_pixel_to_tile)(Console* This, int x, int y, long* px, long* py);
typedef int(__thiscall *FMapWin_tile_to_pixel)(Console* This, int x, int y, long* px, long* py);
typedef int(__thiscall *FMapWin_set_center)(Console* This, int x, int y, int v1);
typedef int(__thiscall *FMapWin)(Console* This);
typedef int(__thiscall *FWin_is_visible)(Win* This);
typedef int(__thiscall *FTutWin_draw_arrow)(Win* This);
typedef int(__thiscall *FPlanWin_blink)(Win* This);
typedef int(__thiscall *FStringBox_clip_ids)(Win* This, int len);
typedef int(__thiscall *FMapWin_gen_map)(Console* This, int owner, int units_only);
typedef int(__thiscall *FMapWin_draw_map)(Console* This, int v1);
typedef int(__stdcall *FWinProc)(HWND, int, WPARAM, LPARAM);
typedef int(__stdcall *FConsole_zoom)(int zoom_type, int v1);
typedef int(__cdecl *FWin_update_screen)(RECT* rt, int v1);
typedef int(__cdecl *FWin_flip)(RECT* rt);
typedef int(__thiscall *FBuffer_set_text_color)(Buffer* This, int color, int a3, int a4, int a5);
typedef int(__thiscall *FBuffer_set_font)(Buffer* This, Font* font, int a3, int a4, int a5);
typedef int(__thiscall *FBuffer_write_l)(Buffer* This, char* text, int x, int y, int max_len);
typedef int(__thiscall *FBuffer_write_cent_l3)(Buffer* This, char* text, RECT* rt, int max_len);
typedef int(__thiscall *FBuffer_box)(Buffer* This, RECT* rt, int color_h, int color_v);
typedef int(__thiscall *FPopup_start)(
    Win* This, const char* filename, const char* label, int a4, int a5, int a6, int a7);
typedef int(__thiscall *FWinGeneric)(Win* This);
typedef int(__thiscall *FGeneric)(void* This);
typedef int(__cdecl *FNetMsg_pop2)(char* label, void* a2);
typedef int(__thiscall *FNetMsg_pop)(void* This, char* label, int delay, int a4, void* a5);

#pragma GCC diagnostic pop


extern FPopup_start Popup_start;
extern FWinGeneric BaseWin_on_redraw;
extern FWinGeneric GraphicWin_redraw;
extern FGeneric SubInterface_release_iface_mode;
extern FMapWin MapWin_calculate_dimensions;
extern FMapWin_tile_to_pixel MapWin_tile_to_pixel;
extern FMapWin_pixel_to_tile MapWin_pixel_to_tile;
extern FMapWin_gen_map MapWin_gen_map;
extern FMapWin_draw_map MapWin_draw_map;
extern fp_void draw_cursor;
extern fp_3int draw_tile;
extern fp_1int draw_map;
extern FMapWin_set_center MapWin_set_center;
extern fp_void MapWin_main_caption;
extern FMapWin MapWin_clear_terrain;
extern FNetMsg_pop NetMsg_pop;
extern FPlanWin_blink PlanWin_blink;
extern Fpopp popp;
extern FGeneric StatusWin_on_redraw;
extern FGeneric StatusWin_redraw;
extern FTutWin_draw_arrow TutWin_draw_arrow;
extern fp_void turn_timer;
extern FConsole_zoom Console_zoom;
extern Fhex_cost hex_cost;
//extern Fhas_abil has_abil;
extern FX_pop X_pop;
extern FX_pops X_pops;
extern FBuffer_set_font Buffer_set_font;
extern FBuffer_set_text_color Buffer_set_text_color;
extern FBuffer_write_l Buffer_write_l;
extern FBuffer_write_l Buffer_write_right_l2;
extern FBuffer_write_cent_l3 Buffer_write_cent_l3;
extern FBuffer_box Buffer_box;
extern FWin_flip Win_flip;
extern FWinProc WinProc;
extern FWin_update_screen Win_update_screen;
extern FWin_is_visible Win_is_visible;
extern tc_2int Font_width;
extern Fpop_ask_number pop_ask_number;
extern FStringBox_clip_ids StringBox_clip_ids;


extern fp_3int terraform_cost;
extern fp_2int action_build;
extern fp_2int contribution;
extern fp_3int action_terraform;
extern fp_1int action_staple;
extern Fact_destroy action_destroy;
extern fp_1int action_go_to;
extern fp_1int action_road_to;
extern fp_2int action_home;
extern Fact_airdrop action_airdrop;
extern fp_3int action_move;
extern fp_1int action_destruct;
extern fp_2int action_oblit;
extern fp_3int sub_4CD6A0;
extern fp_3int action_patrol;
extern fp_5int shoot_it;
extern fp_3int action_tectonic;
extern fp_3int action_fungal;
extern fp_2int action_give;
extern Fact_gate action_gate;
extern fp_4int action_sat_attack;
extern fp_1int action;

//extern fp_1int set_base;
extern fp_2int say_base;
//extern Fbase_at base_at;
extern fp_2int base_find;
extern fp_3int base_find2;
extern fp_6int base_find3;
extern fp_5int whose_territory;
extern fp_3int base_territory;
extern fp_void best_specialist;
extern Fname_base name_base;
extern fp_1int base_mark;
extern fp_3int cost_factor;
extern fp_2int base_making;
extern fp_1int base_lose_minerals;
//extern fp_3int set_fac;
extern fp_3int is_coast;
//extern fp_1int base_first;
extern fp_3int base_init;
extern fp_1int base_kill;
extern fp_2int base_change;
extern fp_2int base_reset;
extern fp_3int bases_reset;
extern fp_3int morale_mod;
extern fp_2int breed_mod;
extern fp_2int worm_mod;
extern fp_void farm_compute;
extern fp_5int crop_yield;
extern fp_5int mine_yield;
extern fp_5int energy_yield;
extern fp_5int resource_yield;
extern fp_void base_yield;
extern fp_void base_support;
extern fp_void base_nutrient;
extern fp_void base_minerals;
extern fp_1int black_market;
extern fp_3int psych_check;
extern fp_void base_psych;
extern fp_2int base_rank;
extern fp_void base_energy;
//extern fp_1int base_compute;
extern fp_1int base_connect;
extern fp_1int base_terraform;
extern fp_1int pop_goal;
extern fp_void base_growth;
extern fp_3int do_upgrade;
extern fp_3int upgrade_cost;
extern fp_4int upgrade_prototype;
extern fp_2int upgrade_prototypes;
extern fp_1int upgrade_any_prototypes;
extern fp_1int base_queue;
extern fp_void base_production;
extern fp_void base_hurry;
extern fp_void base_check_support;
extern fp_void base_energy_costs;
extern fp_void base_research;
extern fp_void drone_riot;
extern fp_void base_drones;
extern fp_void base_doctors;
//extern fp_2int fac_maint;
extern fp_void base_maint;
extern fp_void base_ecology;
extern fp_1int base_upkeep;
extern fp_1int make_base_unique;
//extern fp_2int x_dist;
//extern fp_2int has_project;
extern fp_6int base_claimed;
extern fp_4int base_build;

extern fp_1int drop_range;
extern fp_1int planet_buster2;
extern fp_1int planet_buster;
extern fp_4int shoot;
extern fp_3int planet_busting;
//extern fp_5int defense_value;
extern fp_2int morale_alien;
//extern fp_4int psi_factor;
extern fp_5int get_basic_offense;
extern fp_4int get_basic_defense;
extern fp_5int battle_compute;
extern fp_3int best_defender;
extern fp_3int boom;
extern fp_void sub_505D40;
extern fp_void sub_505D60;
extern fp_6int battle_kill;
extern fp_6int battle_kill_stack;
extern fp_1int promote;
extern fp_1int invasions;
extern fp_4int interceptor;
extern Fbattle_fight_1 battle_fight_1; // renamed
extern fp_7int battle_fight_2; // renamed
extern fp_1int say_num;
extern fp_4int POP3_;
extern fp_1int sub_50B8F0;
extern fp_1int sub_50B910;
extern fp_1int parse_set;
extern fp_3int sub_50B970;
extern fp_1int sub_50B9A0;
extern fp_2int sub_50B9C0;
extern FNetMsg_pop2 NetMsg_pop2;
//extern fp_3int bitmask;
//extern fp_1int bit_count;
extern fp_2int intervention;
extern fp_3int double_cross;
extern fp_2int act_of_aggression;
extern fp_3int steal_tech;
extern fp_1int steal_energy;
extern fp_3int capture_base;

extern fp_1int random_events;
extern fp_void sub_5204E9;
extern fp_void alien_fauna;
extern fp_void do_fungal_towers;
extern fp_4int interlude;
extern fp_void set_time_controls;
extern fp_void reset_territory;
extern fp_1int sub_524340;
extern fp_2int generators;
extern fp_1int end_of_game;
extern fp_void turn_upkeep;
extern fp_1int repair_phase;
extern fp_1int allocate_energy;
extern fp_1int production_phase;
extern fp_1int faction_upkeep;
extern fp_void control_turn;
extern fp_1int net_upkeep_phase;
extern fp_void net_upkeep;
extern fp_void mash_planes;
extern fp_void net_end_of_turn;
extern fp_void net_control_turn;
extern fp_void control_game;
extern fp_1int council_votes;
extern fp_1int eligible;
extern fp_3int wants_prop;
extern fp_3int council_get_vote;
extern fp_2int council_action;
extern fp_2int can_call_council;
extern fp_1int call_council;

extern fp_5int danger;
extern fp_1int my_srand;
extern fp_1int checksum_file;
extern fp_3int checksum;
extern fp_1int checksum_password;
extern fp_void auto_contact;
extern fp_4int net_treaty_on;
extern fp_4int net_treaty_off;
extern fp_5int net_set_treaty;
extern fp_4int net_agenda_off;
extern fp_5int net_set_agenda;
extern fp_5int net_energy;
extern fp_4int net_loan;
extern fp_3int net_maps;
extern fp_4int net_tech;
extern fp_3int net_pact_ends;
extern fp_3int net_cede_base;
extern fp_4int net_double_cross;
extern fp_1int diplo_lock;
extern fp_void diplo_unlock;
extern fp_void sub_5398E0;
extern fp_void sub_539920;
extern fp_2int diplomacy_caption;
extern fp_2int great_beelzebub;
extern fp_2int great_satan;
extern fp_2int aah_ooga;
extern fp_void climactic_battle;
extern fp_1int at_climax;
extern fp_3int cause_friction;
extern fp_1int get_mood;
extern fp_2int reputation;
extern fp_2int get_patience;
extern fp_1int energy_value;
extern fp_2int mention_prototypes;
extern fp_2int scan_prototypes;
extern fp_4int contiguous;
extern fp_3int diplomacy_check;
extern fp_2int pact_withdraw;
extern fp_2int pact_ends;
extern fp_2int pact_of_brotherhood;
extern fp_2int make_treaty;
extern fp_3int pledge_truce;
extern fp_2int introduce;
extern fp_2int wants_to_speak;
extern fp_2int diplomacy_ends;
extern fp_2int demands_withdrawal;
extern fp_2int renounce_pact;
extern fp_2int tech_analysis;
extern fp_4int buy_council_vote;
extern fp_5int buy_tech;
extern fp_2int energy_trade;
extern fp_5int tech_trade;
extern fp_2int trade_maps;
extern fp_2int propose_pact;
extern fp_2int propose_treaty;
extern fp_2int propose_attack;
extern fp_2int make_gift;
extern fp_2int dont_withdrawal;
extern fp_2int do_withdrawal;
extern fp_2int demand_withdrawal;
extern fp_2int threaten;
extern fp_2int suggest_plan;
extern fp_2int attack_from;
extern fp_1int sub_54B140;
extern fp_2int battle_plans;
extern fp_2int call_off_vendetta;
extern fp_2int diplomacy_menu;
extern fp_5int value_of_base;
extern fp_2int give_a_base;
extern fp_2int base_swap;
extern fp_2int proposal_menu;
extern fp_3int make_a_proposal;
extern fp_3int communicate;
extern fp_2int commlink_attempter;
extern fp_1int commlink_attempt;

extern fp_1int pick_top_veh;
extern fp_7int veh_draw;
extern fp_5int sub_55A150;
extern fp_6int base_draw;
extern fp_3int treaty_off;
extern fp_3int agenda_off;
extern fp_3int treaty_on;
extern fp_3int agenda_on;
//extern fp_4int set_treaty;
//extern fp_4int set_agenda;
extern fp_1int spying;
extern fp_3int wants_to_attack;
extern fp_2int comm_check;
extern fp_2int enemies_war;
extern fp_2int pact_unpact;
extern fp_2int enemies_unpact;
extern fp_3int enemies_team_up;
extern fp_2int enemies_trade_tech;
extern fp_3int enemies_treaty;
extern fp_6int encounter;
extern fp_5int territory;
extern fp_4int atrocity;
extern fp_2int major_atrocity;
extern fp_3int break_treaty;
extern fp_1int enemy_diplomacy;
extern fp_4int go_to;
extern fp_1int garrison_check;
extern fp_1int defensive_check;
extern fp_2int guard_check;
extern fp_1int enemy_capabilities;
extern fp_1int enemy_strategy;
extern fp_4int set_course;
extern fp_3int assemble_passengers;
extern fp_2int can_convoy;
extern fp_3int good_sensor;
extern fp_5int can_terraform;
extern fp_5int compute_odds;
extern fp_3int alien_base;
extern fp_1int alien_move;
extern fp_5int air_power;
extern fp_1int enemy_planet_buster;
extern fp_3int get_there;
extern fp_5int coast_or_border;
extern fp_1int enemy_move;
extern fp_1int enemy_veh;
extern fp_1int enemy_turn;
//extern fp_1int rnd;
extern fp_2int cursor_dist;
extern fp_3int site_at;
extern fp_3int is_known;
extern fp_2int base_who;
extern fp_2int anything_at;
extern fp_1int veh_top;
extern fp_1int veh_moves;
extern fp_1int proto_power;
extern fp_2int is_port;
//extern fp_6int add_goal;
//extern fp_5int add_site;
extern fp_4int at_goal;
extern fp_4int at_site;
//extern fp_1int wipe_goals;
extern fp_1int clear_goals;
extern fp_5int del_site;
extern fp_1int want_monolith;
extern fp_1int monolith;
extern fp_1int goody_box;
extern fp_2int valid_tech_leap;
extern fp_1int study_artifact;
extern fp_2int header_check;
extern fp_2int header_write;
extern fp_2int arm_strat;
extern fp_2int weap_strat;
extern fp_2int weap_val;
extern fp_2int arm_val;
extern fp_2int armor_val;
extern fp_3int transport_val;
extern fp_2int say_offense;
extern fp_2int say_defense;
extern fp_2int say_stats_3;
extern fp_2int say_stats_2;
extern fp_3int say_stats;
extern fp_1int clear_bunglist;
extern fp_2int sub_57DF30;
extern fp_6int is_bunged;
extern Fname_proto name_proto;
//extern fp_1int best_reactor;
extern fp_3int pick_chassis;
extern fp_3int weapon_budget;
extern fp_2int retire_proto;
extern fp_3int prune_protos;
extern Fpropose_proto propose_proto;
extern fp_1int abil_index;
extern fp_3int add_abil;
extern fp_1int consider_designs;
extern fp_2int design_new_veh;
extern fp_6int sub_583CD0;
extern fp_2int design_workshop;
extern fp_4int abil_cond;

extern fp_void map_wipe;
extern fp_3int alt_put_detail;
extern fp_3int alt_set;
extern fp_2int alt_natural;
extern fp_3int alt_set_both;
extern fp_2int elev_at;
extern fp_3int climate_set;
extern fp_3int temp_set;
extern fp_3int owner_set;
extern fp_3int site_set;
extern fp_3int region_set;
extern fp_3int rocky_set;
extern fp_3int using_set;
extern fp_3int lock_map;
extern fp_3int unlock_map;
extern fp_3int bit_put;
extern fp_4int bit_set;
extern fp_4int bit2_set;
extern fp_3int code_set;
extern fp_3int synch_bit;
extern fp_2int minerals_at;
extern fp_2int bonus_at;
extern fp_2int goody_at;
extern fp_6int say_loc;
extern fp_2int site_radius;
extern fp_3int find_landmark;
extern fp_3int new_landmark;
extern fp_3int valid_landmark;
extern fp_2int kill_landmark;
extern fp_2int delete_landmark;
extern fp_void fixup_landmarks;
extern fp_void set_dirty;

extern fp_1int tech_name;
extern fp_1int chas_name;
extern fp_1int weap_name;
extern fp_1int arm_name;
extern fp_void read_basic_rules;
extern fp_void read_tech;
extern fp_1int read_faction2;
extern fp_2int read_faction;
extern fp_void read_factions;
extern fp_void read_units;
extern fp_1int read_rules;
extern fp_void sub_5882D0;
extern fp_2int find_font;
extern fp_void scroll_normal;
extern fp_void scroll_small;
extern fp_void popups_normal;
extern fp_void popups_tutorial;
extern fp_void popups_medium;
extern fp_void config_popups;
extern fp_void alien_start;
extern fp_1int planetfall;
extern fp_1int time_controls_dialog;
extern fp_1int thumb_routine;
extern fp_1int change_opening;
extern fp_void close_opening;
extern fp_1int config_game;
extern fp_2int custom_planet;
extern fp_1int size_of_planet;
extern fp_1int map_menu;
extern fp_1int multiplayer_init;
extern fp_1int top_menu;
extern fp_1int desktop_init;
extern fp_void desktop_close;
extern fp_void system_init;
extern fp_void system_close;
extern fp_2int game_init;
extern fp_void game_close;
extern fp_2int game_reload;
extern fp_3int say_special;
extern fp_3int say_fac_special;
extern fp_2int get_phrase;
extern fp_2int get_noun_phrase;
extern fp_1int get_pact;
extern fp_1int get_pacts;
extern fp_2int get_pacts2;
extern fp_2int get_pact_hood;
extern fp_2int get_his_her;
extern fp_2int get_him_her;
extern fp_2int get_he_she;

extern fp_3int vulnerable;
extern fp_3int mind_control;
extern fp_1int corner_market;
extern fp_4int success_rates;
extern fp_4int probe;
extern fp_2int sub_5A58E0;
extern fp_void sub_5A5900;
extern fp_4int sub_5A5910;
extern fp_1int sub_5A5990;
extern fp_3int veh_put;
extern fp_1int veh_health;
extern fp_5int proto_cost;
extern fp_1int base_cost;
extern fp_6int make_proto;
extern fp_1int proto_sort;
extern fp_1int proto_sort_2;
extern fp_3int radius_move;
extern fp_5int radius_move2;
extern fp_4int compass_move;
extern fp_4int encrypt_write;
extern fp_4int encrypt_read;
extern fp_2int game_io;
extern fp_2int game_data;
extern fp_3int map_data;
extern Fsave_daemon save_daemon;
extern fp_void see_map_check;
extern fp_2int load_daemon;
extern fp_1int save_map_daemon;
extern fp_1int load_map_daemon;
extern fp_1int yearmotize;
extern fp_1int save_game;
extern fp_2int load_game;
extern fp_void load_map;
extern fp_void save_map;
extern fp_void kill_auto_save;
extern fp_void auto_save;
extern fp_1int load_undo;
extern fp_void wipe_undo;
extern fp_void auto_undo;
extern fp_2int sub_5ABFF0;
extern fp_1int is_objective;
extern fp_2int num_objectives;
extern fp_2int most_objectives;
extern fp_void ascending;
extern fp_1int rankings;
extern fp_4int compute_score;

extern fp_3int setup_player;
extern fp_2int eliminate_player;
extern fp_void clear_scenario;
extern fp_1int setup_game;
extern fp_5int social_calc;
extern fp_1int social_upkeep;
extern fp_2int sub_5B4550;
extern fp_1int social_set;
extern fp_3int society_avail;
extern fp_6int social_ai;
extern fp_1int social_select;
//extern fp_3int sort;
extern fp_3int sub_5B5700;
extern fp_2int spot_base;
extern fp_2int spot_stack;
extern fp_1int unspot_stack;
extern fp_3int spot_loc;
extern fp_3int want_to_wake;
extern fp_1int wake_stack;
extern fp_2int spot_all;
extern fp_3int stack_put;
extern fp_1int stack_sort;
extern fp_1int stack_sort2;
extern fp_1int stack_fix;
extern fp_2int stack_veh;
extern fp_1int stack_kill;
extern fp_5int stack_check;
//extern fp_void g_WAVE_ctor;
//extern fp_void g_WAVE_dtor;
extern fp_3int say_tech;
extern fp_2int tech_name2;
//extern fp_2int has_tech;
extern fp_2int tech_recurse;
extern fp_1int tech_category;
extern fp_2int redundant;
extern fp_4int facility_avail;
extern fp_3int veh_avail;
extern fp_3int terrain_avail;
extern fp_2int tech_avail;
extern fp_1int tech_effects;
extern fp_4int tech_achieved;
extern fp_3int tech_is_preq;
extern fp_3int tech_val;
extern fp_1int tech_ai;
extern fp_1int tech_mil;
extern fp_1int tech_tech;
extern fp_1int tech_infra;
extern fp_1int tech_colonize;
extern fp_2int wants_prototype;
extern fp_1int tech_selection;
extern fp_1int tech_advance;
extern fp_1int tech_rate;
extern fp_2int tech_research;
extern fp_4int tech_pick;

extern fp_2int veh_at;
extern fp_1int veh_lift;
extern fp_3int veh_drop;
extern fp_1int sleep;
extern fp_1int veh_demote;
extern fp_1int veh_promote;
extern fp_3int veh_clear;
extern fp_4int veh_init;
extern fp_1int veh_kill;
extern fp_1int kill;
extern fp_4int veh_find;
//extern fp_2int can_arty;
extern fp_3int morale_veh;
extern fp_3int offense_proto;
extern fp_3int armor_proto;
extern fp_1int speed_proto;
extern fp_2int speed;
//extern fp_1int veh_cargo;
extern fp_1int prototype_factor;
extern Fveh_cost veh_cost;
extern fp_1int veh_selectable;
extern fp_1int veh_unmoved;
extern fp_1int veh_ready;
extern fp_1int veh_jail;
extern fp_1int veh_skip;
extern fp_2int veh_fake;
extern fp_1int veh_wake;

extern fp_4int world_alt_set;
extern fp_2int world_raise_alt;
extern fp_2int world_lower_alt;
extern fp_3int brush;
extern fp_4int paint_land;
extern fp_1int build_continent;
extern fp_1int build_hills;
extern fp_void world_erosion;
extern fp_void world_rocky;
extern fp_void world_fungus;
extern fp_void world_riverbeds;
extern fp_void world_rivers;
extern fp_void world_shorelines;
extern fp_void world_validate;
extern fp_void world_temperature;
extern fp_void world_rainfall;
extern fp_3int world_site;
extern fp_void world_analysis;
extern fp_void world_polar_caps;
extern fp_void world_climate;
extern fp_void world_linearize_contours;
extern fp_2int near_landmark;
extern fp_2int world_crater;
extern fp_2int world_monsoon;
extern fp_2int world_sargasso;
extern fp_2int world_ruin;
extern fp_2int world_dune;
extern fp_2int world_diamond;
extern fp_2int world_fresh;
extern fp_3int world_volcano;
extern fp_2int world_borehole;
extern fp_2int world_temple;
extern fp_2int world_unity;
extern fp_2int world_fossil;
extern fp_2int world_canyon_nessus;
extern fp_2int world_mesa;
extern fp_2int world_ridge;
extern fp_2int world_geothermal;
extern fp_void world_build;
//extern fp_1int game_year;
extern fp_1int say_year;
extern fp_3int zoc_any;
extern fp_3int zoc_veh;
extern fp_3int zoc_sea;
extern fp_3int zoc_move;

extern fp_void wait_task;
extern fp_void do_task;
extern fp_void do_all_tasks;
extern fp_1int do_all_tasks2;
extern fp_void do_non_input;
extern fp_void do_all_non_input;
extern fp_void do_draw;
extern fp_void do_all_draws;
extern fp_void sub_5FCFE0;
extern fp_void flush_input;
extern fp_void do_sound;
extern fp_void flush_timer;
extern fp_void text_shutdown;
extern fp_void text_dtor;
extern fp_void text_close;
extern fp_2int text_open;
extern fp_void text_get;
extern fp_void text_string;
extern fp_void text_item;
extern fp_void text_item_string;
extern fp_void text_item_number;
extern fp_void text_item_binary;
extern fp_2int parse_string;
extern fp_2int parse_num;
extern fp_4int parse_say;
extern Fparse_says parse_says;


