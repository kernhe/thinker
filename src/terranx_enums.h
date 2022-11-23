#pragma once

const int SP_Unbuilt = -1;
const int SP_Destroyed = -2;
const int SP_ID_First = 70;
const int SP_ID_Last = 106;
const int Fac_ID_First = 1;
const int Fac_ID_Last = 64;
const int Tech_ID_First = 0;
const int Tech_ID_Last = 88;

enum facility_id {
    FAC_HEADQUARTERS = 1,
    FAC_CHILDREN_CRECHE = 2,
    FAC_RECYCLING_TANKS = 3,
    FAC_PERIMETER_DEFENSE = 4,
    FAC_TACHYON_FIELD = 5,
    FAC_RECREATION_COMMONS = 6,
    FAC_ENERGY_BANK = 7,
    FAC_NETWORK_NODE = 8,
    FAC_BIOLOGY_LAB = 9,
    FAC_SKUNKWORKS = 10,
    FAC_HOLOGRAM_THEATRE = 11,
    FAC_PARADISE_GARDEN = 12,
    FAC_TREE_FARM = 13,
    FAC_HYBRID_FOREST = 14,
    FAC_FUSION_LAB = 15,
    FAC_QUANTUM_LAB = 16,
    FAC_RESEARCH_HOSPITAL = 17,
    FAC_NANOHOSPITAL = 18,
    FAC_ROBOTIC_ASSEMBLY_PLANT = 19,
    FAC_NANOREPLICATOR = 20,
    FAC_QUANTUM_CONVERTER = 21,
    FAC_GENEJACK_FACTORY = 22,
    FAC_PUNISHMENT_SPHERE = 23,
    FAC_HAB_COMPLEX = 24,
    FAC_HABITATION_DOME = 25,
    FAC_PRESSURE_DOME = 26,
    FAC_COMMAND_CENTER = 27,
    FAC_NAVAL_YARD = 28,
    FAC_AEROSPACE_COMPLEX = 29,
    FAC_BIOENHANCEMENT_CENTER = 30,
    FAC_CENTAURI_PRESERVE = 31,
    FAC_TEMPLE_OF_PLANET = 32,
    FAC_PSI_GATE = 33,
    FAC_COVERT_OPS_CENTER = 34,
    FAC_BROOD_PIT = 35,
    FAC_AQUAFARM = 36,
    FAC_SUBSEA_TRUNKLINE = 37,
    FAC_THERMOCLINE_TRANSDUCER = 38,
    FAC_FLECHETTE_DEFENSE_SYS = 39,
    FAC_SUBSPACE_GENERATOR = 40,
    FAC_GEOSYNC_SURVEY_POD = 41,
    FAC_EMPTY_FACILITY_42 = 42,
    FAC_EMPTY_FACILITY_43 = 43,
    FAC_EMPTY_FACILITY_44 = 44,
    FAC_EMPTY_FACILITY_45 = 45,
    FAC_EMPTY_FACILITY_46 = 46,
    FAC_EMPTY_FACILITY_47 = 47,
    FAC_EMPTY_FACILITY_48 = 48,
    FAC_EMPTY_FACILITY_49 = 49,
    FAC_EMPTY_FACILITY_50 = 50,
    FAC_EMPTY_FACILITY_51 = 51,
    FAC_EMPTY_FACILITY_52 = 52,
    FAC_EMPTY_FACILITY_53 = 53,
    FAC_EMPTY_FACILITY_54 = 54,
    FAC_EMPTY_FACILITY_55 = 55,
    FAC_EMPTY_FACILITY_56 = 56,
    FAC_EMPTY_FACILITY_57 = 57,
    FAC_EMPTY_FACILITY_58 = 58,
    FAC_EMPTY_FACILITY_59 = 59,
    FAC_EMPTY_FACILITY_60 = 60,
    FAC_EMPTY_FACILITY_61 = 61,
    FAC_EMPTY_FACILITY_62 = 62,
    FAC_EMPTY_FACILITY_63 = 63,
    FAC_EMPTY_FACILITY_64 = 64,
    FAC_SKY_HYDRO_LAB = 65,
    FAC_NESSUS_MINING_STATION = 66,
    FAC_ORBITAL_POWER_TRANS = 67,
    FAC_ORBITAL_DEFENSE_POD = 68,
    FAC_STOCKPILE_ENERGY = 69,
    FAC_HUMAN_GENOME_PROJ = 70,
    FAC_COMMAND_NEXUS = 71,
    FAC_WEATHER_PARADIGM = 72,
    FAC_MERCHANT_EXCHANGE = 73,
    FAC_EMPATH_GUILD = 74,
    FAC_CITIZENS_DEFENSE_FORCE = 75,
    FAC_VIRTUAL_WORLD = 76,
    FAC_PLANETARY_TRANS_SYS = 77,
    FAC_XENOEMPATHY_DOME = 78,
    FAC_NEURAL_AMPLIFIER = 79,
    FAC_MARITIME_CONTROL_CENTER = 80,
    FAC_PLANETARY_DATALINKS = 81,
    FAC_SUPERCOLLIDER = 82,
    FAC_ASCETIC_VIRTUES = 83,
    FAC_LONGEVITY_VACCINE = 84,
    FAC_HUNTER_SEEKER_ALGO = 85,
    FAC_PHOLUS_MUTAGEN = 86,
    FAC_CYBORG_FACTORY = 87,
    FAC_THEORY_OF_EVERYTHING = 88,
    FAC_DREAM_TWISTER = 89,
    FAC_UNIVERSAL_TRANSLATOR = 90,
    FAC_NETWORK_BACKBONE = 91,
    FAC_NANO_FACTORY = 92,
    FAC_LIVING_REFINERY = 93,
    FAC_CLONING_VATS = 94,
    FAC_SELF_AWARE_COLONY = 95,
    FAC_CLINICAL_IMMORTALITY = 96,
    FAC_SPACE_ELEVATOR = 97,
    FAC_SINGULARITY_INDUCTOR = 98,
    FAC_BULK_MATTER_TRANSMITTER = 99,
    FAC_TELEPATHIC_MATRIX = 100,
    FAC_VOICE_OF_PLANET = 101,
    FAC_ASCENT_TO_TRANSCENDENCE = 102,
    FAC_MANIFOLD_HARMONICS = 103,
    FAC_NETHACK_TERMINUS = 104,
    FAC_CLOUDBASE_ACADEMY = 105,
    FAC_PLANETARY_ENERGY_GRID = 106,
    FAC_EMPTY_SP_38 = 107,
    FAC_EMPTY_SP_39 = 108,
    FAC_EMPTY_SP_40 = 109,
    FAC_EMPTY_SP_41 = 110,
    FAC_EMPTY_SP_42 = 111,
    FAC_EMPTY_SP_43 = 112,
    FAC_EMPTY_SP_44 = 113,
    FAC_EMPTY_SP_45 = 114,
    FAC_EMPTY_SP_46 = 115,
    FAC_EMPTY_SP_47 = 116,
    FAC_EMPTY_SP_48 = 117,
    FAC_EMPTY_SP_49 = 118,
    FAC_EMPTY_SP_50 = 119,
    FAC_EMPTY_SP_51 = 120,
    FAC_EMPTY_SP_52 = 121,
    FAC_EMPTY_SP_53 = 122,
    FAC_EMPTY_SP_54 = 123,
    FAC_EMPTY_SP_55 = 124,
    FAC_EMPTY_SP_56 = 125,
    FAC_EMPTY_SP_57 = 126,
    FAC_EMPTY_SP_58 = 127,
    FAC_EMPTY_SP_59 = 128,
    FAC_EMPTY_SP_60 = 129,
    FAC_EMPTY_SP_61 = 130,
    FAC_EMPTY_SP_62 = 131,
    FAC_EMPTY_SP_63 = 132,
    FAC_EMPTY_SP_64 = 133,
};

enum technology_id {
    TECH_Biogen = 0,
    TECH_Indust = 1,
    TECH_InfNet = 2,
    TECH_Physic = 3,
    TECH_Psych = 4,
    TECH_Mobile = 5,
    TECH_Ecology = 6,
    TECH_Super = 7,
    TECH_Chaos = 8,
    TECH_E_Mc2 = 9,
    TECH_Fusion = 10,
    TECH_Alloys = 11,
    TECH_Subat = 12,
    TECH_Chemist = 13,
    TECH_Surface = 14,
    TECH_Metal = 15,
    TECH_String = 16,
    TECH_MilAlg = 17,
    TECH_Magnets = 18,
    TECH_MatComp = 19,
    TECH_Unified = 20,
    TECH_Gravity = 21,
    TECH_Poly = 22,
    TECH_AGrav = 23,
    TECH_deleted_1 = 24,
    TECH_Quantum = 25,
    TECH_SingMec = 26,
    TECH_ConSing = 27,
    TECH_TempMec = 28,
    TECH_ProbMec = 29,
    TECH_Algor = 30,
    TECH_Solids = 31,
    TECH_PlaNets = 32,
    TECH_DigSent = 33,
    TECH_HAL9000 = 34,
    TECH_DocInit = 35,
    TECH_DocFlex = 36,
    TECH_Integ = 37,
    TECH_Fossil = 38,
    TECH_DocAir = 39,
    TECH_DocSec = 40,
    TECH_MindMac = 41,
    TECH_NanoMin = 42,
    TECH_DocLoy = 43,
    TECH_EthCalc = 44,
    TECH_IndEcon = 45,
    TECH_IndAuto = 46,
    TECH_CentMed = 47,
    TECH_Brain = 48,
    TECH_Gene = 49,
    TECH_BioEng = 50,
    TECH_BioMac = 51,
    TECH_Neural = 52,
    TECH_Cyber = 53,
    TECH_Eudaim = 54,
    TECH_WillPow = 55,
    TECH_Thresh = 56,
    TECH_Matter = 57,
    TECH_CentEmp = 58,
    TECH_EnvEcon = 59,
    TECH_EcoEng = 60,
    TECH_PlaEcon = 61,
    TECH_EcoEng2 = 62,
    TECH_CentPsi = 63,
    TECH_AlphCen = 64,
    TECH_Create = 65,
    TECH_Space = 66,
    TECH_HomoSup = 67,
    TECH_SupLube = 68,
    TECH_QuanMac = 69,
    TECH_deleted_2 = 70,
    TECH_NanEdit = 71,
    TECH_OptComp = 72,
    TECH_IndRob = 73,
    TECH_CentGen = 74,
    TECH_SentEco = 75,
    TECH_Viral = 76,
    TECH_Orbital = 77,
    TECH_PrPsych = 78,
    TECH_FldMod = 79,
    TECH_AdapDoc = 80,
    TECH_AdapEco = 81,
    TECH_Bioadap = 82,
    TECH_SentRes = 83,
    TECH_SecMani = 84,
    TECH_NewMiss = 85,
    TECH_BFG9000 = 86,
    TECH_User = 87,
    TECH_TranT = 88,
    TECH_None = -1,
    TECH_Disable = -2,
};

enum tech_flags {
    TECH_FLAGS_SECRETS = 0x1,
    TECH_FLAGS_IMPROVE_PROBE = 0x2,
    TECH_FLAGS_INC_COMMERCE = 0x4,
    TECH_FLAGS_REVEALS_MAP = 0x8,
    TECH_FLAGS_ALLOW_GENE_WARFARE = 0x10,
    TECH_FLAGS_INC_DEFENSE_GENE_WARFARE = 0x20,
    TECH_FLAGS_INC_ENERGY_FUNGUS = 0x40,
    TECH_FLAGS_INC_MINERALS_FUNGUS = 0x80,
    TECH_FLAGS_INC_NUTRIENT_FUNGUS = 0x100,
};

enum Triad {
    TRIAD_NONE = -1, // Thinker variable
    TRIAD_LAND = 0,
    TRIAD_SEA = 1,
    TRIAD_AIR = 2,
};

enum VehBasicUnit {
    BSC_COLONY_POD = 0,
    BSC_FORMERS = 1,
    BSC_SCOUT_PATROL = 2,
    BSC_TRANSPORT_FOIL = 3,
    BSC_SEA_FORMERS = 4,
    BSC_SUPPLY_CRAWLER = 5,
    BSC_PROBE_TEAM = 6,
    BSC_ALIEN_ARTIFACT = 7,
    BSC_MIND_WORMS = 8,
    BSC_ISLE_OF_THE_DEEP = 9,
    BSC_LOCUSTS_OF_CHIRON = 10,
    BSC_UNITY_ROVER = 11,
    BSC_UNITY_SCOUT_CHOPPER = 12,
    BSC_UNITY_FOIL = 13,
    BSC_SEALURK = 14,
    BSC_SPORE_LAUNCHER = 15,
    BSC_BATTLE_OGRE_MK1 = 16,
    BSC_BATTLE_OGRE_MK2 = 17,
    BSC_BATTLE_OGRE_MK3 = 18,
    BSC_FUNGAL_TOWER = 19,
    BSC_UNITY_MINING_LASER = 20,
    BSC_SEA_ESCAPE_POD = 21,
    BSC_UNITY_GUNSHIP = 22,
};

enum VehChassis {
    CHS_INFANTRY = 0,
    CHS_SPEEDER = 1,
    CHS_HOVERTANK = 2,
    CHS_FOIL = 3,
    CHS_CRUISER = 4,
    CHS_NEEDLEJET = 5,
    CHS_COPTER = 6,
    CHS_GRAVSHIP = 7,
    CHS_MISSILE = 8,
};

enum VehReactor {
    REC_FISSION = 1,
    REC_FUSION = 2,
    REC_QUANTUM = 3,
    REC_SINGULARITY = 4,
};

enum VehArmor {
    ARM_NO_ARMOR = 0,
    ARM_SYNTHMETAL_ARMOR = 1,
    ARM_PLASMA_STEEL_ARMOR = 2,
    ARM_SILKSTEEL_ARMOR = 3,
    ARM_PHOTON_WALL = 4,
    ARM_PROBABILITY_SHEATH = 5,
    ARM_NEUTRONIUM_ARMOR = 6,
    ARM_ANTIMATTER_PLATE = 7,
    ARM_STASIS_GENERATOR = 8,
    ARM_PSI_DEFENSE = 9,
    ARM_PULSE_3_ARMOR = 10,
    ARM_RESONANCE_3_ARMOR = 11,
    ARM_PULSE_8_ARMOR = 12,
    ARM_RESONANCE_8_ARMOR = 13,
};

enum VehWeapon {
    WPN_HAND_WEAPONS = 0,
    WPN_LASER = 1,
    WPN_PARTICLE_IMPACTOR = 2,
    WPN_GATLING_LASER = 3,
    WPN_MISSILE_LAUNCHER = 4,
    WPN_CHAOS_GUN = 5,
    WPN_FUSION_LASER = 6,
    WPN_TACHYON_BOLT = 7,
    WPN_PLASMA_SHARD = 8,
    WPN_QUANTUM_LASER = 9,
    WPN_GRAVITON_GUN = 10,
    WPN_SINGULARITY_LASER = 11,
    WPN_RESONANCE_LASER = 12,
    WPN_RESONANCE_BOLT = 13,
    WPN_STRING_DISRUPTOR = 14,
    WPN_PSI_ATTACK = 15,
    WPN_PLANET_BUSTER = 16,
    WPN_COLONY_MODULE = 17,
    WPN_TERRAFORMING_UNIT = 18,
    WPN_TROOP_TRANSPORT = 19,
    WPN_SUPPLY_TRANSPORT = 20,
    WPN_PROBE_TEAM = 21,
    WPN_ALIEN_ARTIFACT = 22,
    WPN_CONVENTIONAL_PAYLOAD = 23,
    WPN_TECTONIC_PAYLOAD = 24,
    WPN_FUNGAL_PAYLOAD = 25,
};

enum VehWeaponMode {
    WMODE_COMBAT = 0, // Thinker variable
    WMODE_PROJECTILE = 0,
    WMODE_ENERGY = 1,
    WMODE_MISSILE = 2,
    WMODE_TRANSPORT = 7,
    WMODE_COLONIST = 8,
    WMODE_TERRAFORMER = 9,
    WMODE_CONVOY = 10,
    WMODE_INFOWAR = 11,
    WMODE_ARTIFACT = 12,
};

enum VehPlan {
    PLAN_OFFENSIVE = 0,
    PLAN_COMBAT = 1,
    PLAN_DEFENSIVE = 2,
    PLAN_RECONNAISANCE = 3,
    PLAN_AIR_SUPERIORITY = 4,
    PLAN_PLANET_BUSTER = 5,
    PLAN_NAVAL_SUPERIORITY = 6,
    PLAN_NAVAL_TRANSPORT = 7,
    PLAN_COLONIZATION = 8,
    PLAN_TERRAFORMING = 9,
    PLAN_SUPPLY_CONVOY = 10,
    PLAN_INFO_WARFARE = 11,
    PLAN_ALIEN_ARTIFACT = 12,
    PLAN_TECTONIC_MISSILE = 13,
    PLAN_FUNGAL_MISSILE = 14,
    PLAN_AUTO_CALCULATE = -1,
};

enum VehAbility {
    ABL_ID_SUPER_TERRAFORMER = 0,
    ABL_ID_DEEP_RADAR = 1,
    ABL_ID_CLOAKED = 2,
    ABL_ID_AMPHIBIOUS = 3,
    ABL_ID_DROP_POD = 4,
    ABL_ID_AIR_SUPERIORITY = 5,
    ABL_ID_DEEP_PRESSURE_HULL = 6,
    ABL_ID_CARRIER = 7,
    ABL_ID_AAA = 8,
    ABL_ID_COMM_JAMMER = 9,
    ABL_ID_ANTIGRAV_STRUTS = 10,
    ABL_ID_EMPATH = 11,
    ABL_ID_POLY_ENCRYPTION = 12,
    ABL_ID_FUNGICIDAL = 13,
    ABL_ID_TRAINED = 14,
    ABL_ID_ARTILLERY = 15,
    ABL_ID_CLEAN_REACTOR = 16,
    ABL_ID_BLINK_DISPLACER = 17,
    ABL_ID_TRANCE = 18,
    ABL_ID_HEAVY_TRANSPORT = 19,
    ABL_ID_NERVE_GAS = 20,
    ABL_ID_REPAIR = 21,
    ABL_ID_POLICE_2X = 22,
    ABL_ID_SLOW = 23,
    ABL_ID_SOPORIFIC_GAS = 24,
    ABL_ID_DISSOCIATIVE_WAVE = 25,
    ABL_ID_MARINE_DETACHMENT = 26,
    ABL_ID_FUEL_NANOCELLS = 27,
    ABL_ID_ALGO_ENHANCEMENT = 28,
};

enum VehAbilityFlag {
    ABL_NONE = 0,
    ABL_SUPER_TERRAFORMER = 0x1,
    ABL_DEEP_RADAR = 0x2,
    ABL_CLOAKED = 0x4,
    ABL_AMPHIBIOUS = 0x8,
    ABL_DROP_POD = 0x10,
    ABL_AIR_SUPERIORITY = 0x20,
    ABL_DEEP_PRESSURE_HULL = 0x40,
    ABL_CARRIER = 0x80,
    ABL_AAA = 0x100,
    ABL_COMM_JAMMER = 0x200,
    ABL_ANTIGRAV_STRUTS = 0x400,
    ABL_EMPATH = 0x800,
    ABL_POLY_ENCRYPTION = 0x1000,
    ABL_FUNGICIDAL = 0x2000,
    ABL_TRAINED = 0x4000,
    ABL_ARTILLERY = 0x8000,
    ABL_CLEAN_REACTOR = 0x10000,
    ABL_BLINK_DISPLACER = 0x20000,
    ABL_TRANCE = 0x40000,
    ABL_HEAVY_TRANSPORT = 0x80000,
    ABL_NERVE_GAS = 0x100000,
    ABL_REPAIR = 0x200000,
    ABL_POLICE_2X = 0x400000,
    ABL_SLOW = 0x800000,
    ABL_SOPORIFIC_GAS = 0x1000000,
    ABL_DISSOCIATIVE_WAVE = 0x2000000,
    ABL_MARINE_DETACHMENT = 0x4000000,
    ABL_FUEL_NANOCELLS = 0x8000000,
    ABL_ALGO_ENHANCEMENT = 0x10000000,
};

enum VehAbilityRules {
    AFLAG_ALLOWED_LAND_UNIT = 0x1,
    AFLAG_ALLOWED_SEA_UNIT = 0x2,
    AFLAG_ALLOWED_AIR_UNIT = 0x4,
    AFLAG_ALLOWED_COMBAT_UNIT = 0x8,
    AFLAG_ALLOWED_TERRAFORM_UNIT = 0x10,
    AFLAG_ALLOWED_NONCOMBAT_UNIT = 0x20,
    AFLAG_NOT_ALLOWED_PROBE_TEAM = 0x40,
    AFLAG_NOT_ALLOWED_PSI_UNIT = 0x80,
    AFLAG_TRANSPORT_ONLY_UNIT = 0x100,
    AFLAG_NOT_ALLOWED_FAST_UNIT = 0x200,
    AFLAG_COST_INC_LAND_UNIT = 0x400,
    AFLAG_ONLY_PROBE_TEAM = 0x800,
};

enum unit_prototype_flags {
    UNIT_ACTIVE = 0x1, // if this bit is zero, prototype has been retired
    UNIT_CUSTOM_NAME_SET = 0x2,
    UNIT_PROTOTYPED = 0x4,
};

enum veh_flags {
    VFLAG_PROBE_PACT_OPERATIONS = 0x4,
    VFLAG_IS_OBJECTIVE = 0x20,
    VFLAG_LURKER = 0x40,
    VFLAG_START_RAND_LOCATION = 0x80,
    VFLAG_START_RAND_MONOLITH = 0x100,
    VFLAG_START_RAND_FUNGUS = 0x200,
    VFLAG_INVISIBLE = 0x400,
};

enum veh_state {
    VSTATE_IN_TRANSPORT = 0x1,
    VSTATE_UNK_2 = 0x2,
    VSTATE_HAS_MOVED = 0x4, // set after first movement attempt (even if failed) on each turn
    VSTATE_UNK_8 = 0x8,
    VSTATE_REQUIRES_SUPPORT = 0x10,
    VSTATE_MADE_AIRDROP = 0x20,
    VSTATE_UNK_40 = 0x40,
    VSTATE_DESIGNATE_DEFENDER = 0x80,
    VSTATE_MONOLITH_UPGRADED = 0x100,
    VSTATE_UNK_200 = 0x200,
    VSTATE_UNK_400 = 0x400,
    VSTATE_UNK_800 = 0x800,
    VSTATE_UNK_1000 = 0x1000,
    VSTATE_UNK_2000 = 0x2000,
    VSTATE_EXPLORE = 0x4000,
    VSTATE_UNK_8000 = 0x8000,
    VSTATE_UNK_10000 = 0x10000,
    VSTATE_UNK_20000 = 0x20000,
    VSTATE_UNK_40000 = 0x40000,
    VSTATE_USED_NERVE_GAS = 0x80000, // set/reset on attacking Veh after each attack
    VSTATE_UNK_100000 = 0x100000,
    VSTATE_PACIFISM_DRONE = 0x200000,
    VSTATE_PACIFISM_FREE_SKIP = 0x400000,
    VSTATE_ASSISTANT_WORM = 0x800000, // Int: Brood Trainer; Human player's 1st spawned Mind Worm
    VSTATE_UNK_1000000 = 0x1000000,
    VSTATE_UNK_2000000 = 0x2000000,
    VSTATE_CRAWLING = 0x4000000, // more than just crawling, terraforming also?
    VSTATE_UNK_8000000 = 0x8000000,
    VSTATE_UNK_10000000 = 0x10000000,
    VSTATE_UNK_20000000 = 0x20000000,
    VSTATE_UNK_40000000 = 0x40000000,
    VSTATE_UNK_80000000 = 0x80000000,
};

enum veh_morale {
    MORALE_VERY_GREEN = 0,
    MORALE_GREEN = 1,
    MORALE_DISCIPLINED = 2,
    MORALE_HARDENED = 3,
    MORALE_VETERAN = 4,
    MORALE_COMMANDO = 5,
    MORALE_ELITE = 6,
};

enum probe_action {
    PRB_INFILTRATE_DATALINKS = 0,
    PRB_PROCURE_RESEARCH_DATA = 1,
    PRB_ACTIVATE_SABOTAGE_VIRUS = 2,
    PRB_DRAIN_ENERGY_RESERVES = 3,
    PRB_INCITE_DRONE_RIOTS = 4,
    PRB_ASSASSINATE_PROMINENT_RESEARCHERS = 5,
    PRB_MIND_CONTROL_CITY = 6,
    PRB_INTRODUCE_GENETIC_PLAGUE = 7,
    PRB_FREE_CAPTURED_FACTION_LEADER = 8,
    PRB_MIND_CONTROL_UNIT = -1,
};

enum social_effect {
    SE_ECONOMY = 0,
    SE_EFFIC = 1,
    SE_SUPPORT = 2,
    SE_TALENT = 3,
    SE_MORALE = 4,
    SE_POLICE = 5,
    SE_GROWTH = 6,
    SE_PLANET = 7,
    SE_PROBE = 8,
    SE_INDUSTRY = 9,
    SE_RESEARCH = 10,
};

enum game_state {
    STATE_GAME_DONE = 0x1,
    STATE_UNK_2 = 0x2,
    STATE_UNK_4 = 0x4,
    STATE_FINAL_SCORE_DONE = 0x8, // end game score screen has been shown to player
    STATE_IS_SCENARIO = 0x10,
    STATE_SCENARIO_CHEATED_FLAG = 0x20,
    STATE_SCENARIO_EDITOR = 0x40,
    STATE_OMNISCIENT_VIEW = 0x80,
    STATE_UNK_100 = 0x100, // set or unset in Path::continents
    STATE_UNK_200 = 0x200,
    STATE_UNK_400 = 0x400,
    STATE_UNK_800 = 0x800, // time expired? MP related? NOBONUSATEND
    STATE_DEBUG_MODE = 0x1000,
    STATE_VICTORY_CONQUER = 0x2000,
    STATE_DISPLAYED_COUNCIL_AVAIL_MSG = 0x4000, // set when #COUNCILOPEN is displayed to show once
    STATE_SCN_VICT_TERRITORY_COUNT_OBJ = 0x8000,
    STATE_COUNCIL_HAS_CONVENED = 0x10000, // set 1st time Planetary Council is convened
    STATE_VOLCANO_ERUPTED = 0x20000, // #VOLCANO, tied to Planet ecology; can only be triggered once
    STATE_SCN_VICT_ALL_ARTIFACTS_OBJ_UNIT = 0x40000,
    STATE_SCN_VICT_HIGHEST_AC_SCORE_WINS = 0x80000,
    STATE_PERIHELION_ACTIVE = 0x100000,
    STATE_VICTORY_DIPLOMATIC = 0x200000,
    STATE_VICTORY_ECONOMIC = 0x400000,
    STATE_RAND_FAC_LEADER_PERSONALITIES = 0x800000,
    STATE_RAND_FAC_LEADER_SOCIAL_AGENDA = 0x1000000,
    STATE_SCN_VICT_TERRAIN_ENH_COUNT_OBJ = 0x2000000,
    STATE_SCN_VICT_BASE_FACIL_COUNT_OBJ = 0x4000000,
    STATE_EDITOR_ONLY_MODE = 0x8000000,
    STATE_UNK_10000000 = 0x10000000,
    STATE_SCN_VICT_POPULATION_COUNT_OBJ = 0x20000000,
    STATE_SCN_VICT_TECH_COUNT_OBJ = 0x40000000,
    STATE_SCN_VICT_CREDITS_COUNT_OBJ = 0x80000000,
};

enum game_rules {
    RULES_DO_OR_DIE = 0x1,
    RULES_VICTORY_CONQUEST = 0x2,
    RULES_VICTORY_ECONOMIC = 0x4,
    RULES_VICTORY_DIPLOMATIC = 0x8,
    RULES_LOOK_FIRST = 0x10,
    RULES_TECH_STAGNATION = 0x20,
    RULES_INTENSE_RIVALRY = 0x40,
    RULES_TIME_WARP = 0x80,
    RULES_NO_UNITY_SURVEY = 0x100,
    RULES_BLIND_RESEARCH = 0x200,
    RULES_IRONMAN = 0x400,
    RULES_VICTORY_TRANSCENDENCE = 0x800,
    RULES_VICTORY_COOPERATIVE = 0x1000,
    RULES_NO_UNITY_SCATTERING = 0x2000,
    RULES_SPOILS_OF_WAR = 0x4000,
    RULES_BELL_CURVE = 0x8000,
    RULES_SCN_UNITY_PODS_NO_RESOURCES = 0x10000,
    RULES_SCN_UNITY_PODS_NO_MONOLITHS = 0x20000,
    RULES_SCN_UNITY_PODS_NO_ARTIFACTS = 0x40000,
    RULES_SCN_VICT_SOLO_MISSION = 0x80000,
    RULES_SCN_FORCE_PLAYER_PLAY_CURRENT_FACT = 0x100000,
    RULES_SCN_NO_NATIVE_LIFE = 0x200000,
    RULES_SCN_NO_COLONY_PODS = 0x400000,
    RULES_SCN_NO_TERRAFORMING = 0x800000,
    RULES_SCN_FORCE_CURRENT_DIFF_LEVEL = 0x1000000,
    RULES_SCN_NO_TECH_TRADING = 0x2000000,
    RULES_SCN_NO_TECH_ADVANCES = 0x4000000,
    RULES_SCN_VICT_OBJ_UNITS_REACH_FRIEND_OBJ_BASE = 0x8000000,
    RULES_SCN_VICT_OBJ_UNITS_REACH_FRIEND_HQ_BASE = 0x10000000,
    RULES_SCN_VICT_ALL_BASE_COUNT_OBJ = 0x20000000,
    RULES_SCN_VICT_SP_COUNT_OBJ = 0x40000000,
    RULES_SCN_NO_BUILDING_SP = 0x80000000,
};

enum GameBaseWarningsBitfield {
    WARN_STOP_NEW_FAC_BUILT = 0x1,
    WARN_STOP_NON_COMBAT_VEH_BUILT = 0x2,
    WARN_STOP_PROTOTYPE_COMPLETE = 0x4,
    WARN_STOP_DRONE_RIOTS = 0x8,
    WARN_STOP_DRONE_RIOTS_END = 0x10,
    WARN_STOP_GOLDEN_AGE = 0x20,
    WARN_STOP_GOLDEN_AGE_END = 0x40,
    WARN_STOP_NUTRIENT_SHORTAGE = 0x80,
    WARN_STOP_UNK_100 = 0x100, // no text, not visible in PrefWin; set with default warning
    WARN_STOP_BUILD_OUT_OF_DATE = 0x200,
    WARN_STOP_COMBAT_VEH_BUILT = 0x400,
    WARN_STOP_POP_LIMIT_REACHED = 0x800,
    WARN_STOP_DELAY_IN_TRANSCEND = 0x1000,
    WARN_STOP_BUILT_VIA_GOV_QUEUE = 0x2000,
    WARN_STOP_STARVATION = 0x4000,
    WARN_STOP_MINERAL_SHORTAGE = 0x8000,
    WARN_STOP_ENERGY_SHORTAGE = 0x10000,
    WARN_STOP_RANDOM_EVENT = 0x20000,
};

enum GamePreferencesBitfield {
    PREF_BSC_PAUSE_END_TURN = 0x1,
    PREF_BSC_AUTOSAVE_EACH_TURN = 0x2,
    PREF_BSC_DONT_QUICK_MOVE_ENEMY_VEH = 0x4, // flag set when unchecked
    PREF_ADV_FAST_BATTLE_RESOLUTION = 0x8,
    PREF_UNK_10 = 0x10, // no text, not visible in PrefWin; set with default preferences
    PREF_BSC_TUTORIAL_MSGS = 0x20,
    //
    PREF_AV_MAP_ANIMATIONS = 0x80,
    PREF_MAP_SHOW_GRID = 0x100,
    PREF_MAP_SHOW_BASE_GRID = 0x200,
    PREF_AV_VOLUME_SFX_TOGGLE = 0x400,
    PREF_AV_SOUND_EFFECTS = 0x400, // not displayed
    PREF_AV_VOLUME_MUSIC_TOGGLE = 0x800,
    PREF_AV_BACKGROUND_MUSIC = 0x800, // not displayed
    PREF_BSC_MOUSE_EDGE_SCROLL_VIEW = 0x1000,
    //
    PREF_BSC_AUTO_DESIGN_VEH = 0x4000,
    PREF_BSC_DONT_QUICK_MOVE_ALLY_VEH = 0x8000, // flag set when unchecked
    PREF_AUTO_AIR_VEH_RET_HOME_FUEL_RNG = 0x10000,
    PREF_AUTO_FORMER_RAISE_LWR_TERRAIN = 0x20000,
    PREF_AV_INTERLUDES_DISABLED = 0x40000, // flag set when unchecked
    PREF_ADV_NO_CENTER_VEH_ORDERS = 0x80000,
    PREF_AUTO_END_MOVE_SPOT_VEH_PACT = 0x100000,
    PREF_AUTO_END_MOVE_SPOT_VEH_TREATY = 0x200000,
    PREF_AUTO_END_MOVE_SPOT_VEH_TRUCE = 0x400000,
    PREF_AUTO_END_MOVE_SPOT_VEH_WAR = 0x800000,
    PREF_AUTO_FORMER_PLANT_FORESTS = 0x1000000,
    PREF_AUTO_FORMER_BUILD_ADV = 0x2000000, // condensers, boreholes, etc.
    //
    PREF_AV_SLIDING_WINDOWS = 0x8000000,
    PREF_AV_SECRET_PROJECT_MOVIES = 0x10000000,
    PREF_ADV_RADIO_BTN_NOT_SEL_SING_CLK = 0x20000000, // flag set when unchecked
    PREF_AUTO_DONT_END_MOVE_DIFF_TRIAD = 0x40000000,
    PREF_AUTO_WAKE_VEH_TRANS_REACH_LAND = 0x80000000,
};

enum GameMorePreferencesBitfield {
    MPREF_MAP_SHOW_FOG_WAR = 0x1,
    //
    MPREF_ADV_ZOOM_BASE_NO_RECENTER_MAP = 0x4,
    MPREF_AUTO_FORMER_REMOVE_FUNGUS = 0x8,
    MPREF_ADV_PAUSE_AFTER_BATTLES = 0x10,
    MPREF_AUTO_FORMER_BUILD_SENSORS = 0x20,
    MPREF_ADV_QUICK_MOVE_VEH_ORDERS = 0x40,
    MPREF_ADV_QUICK_MOVE_ALL_VEH = 0x80,
    MPREF_ADV_RIGHT_CLICK_POPS_UP_MENU = 0x100,
    MPREF_AV_WHOLE_VEH_BLINKS = 0x200,
    MPREF_ADV_DETAIL_RIGHT_CLICK_MENUS = 0x400,
    MPREF_AUTO_ALWAYS_INSPECT_MONOLITH = 0x800,
    MPREF_MAP_SHOW_PROD_WITH_BASE_NAMES = 0x1000,
    MPREF_MAP_SHOW_BASE_NAMES = 0x2000,
    MPREF_AV_VOLUME_VOICE_TOGGLE = 0x4000,
    MPREF_AV_VOICEOVER_TECH_FAC = 0x4000, // not displayed
    MPREF_ADV_CONFIRM_ODDS_BF_ATTACKING = 0x8000,
    MPREF_MAP_SHOW_FLAT_TERRAIN = 0x10000,
    MPREF_AV_VOICEOVER_STOP_CLOSE_POPUP = 0x20000,
    MPREF_ADV_CLICK_VEH_CANCELS_ORDERS = 0x40000,
    MPREF_AV_SLIDING_SCROLLBARS = 0x80000,
    MPREF_BSC_AUTO_PRUNE_OBS_VEH = 0x100000,
    MPREF_ADV_DETAIL_MAIN_MENUS = 0x200000,
    MPREF_AUTO_FORMER_CANT_BUILD_ROADS = 0x400000, // or tubes; flag set when unchecked
    MPREF_MAP_SHOW_GRID_OCEAN_SQ = 0x800000,
    MPREF_AV_MONUMENTS_DISABLED = 0x1000000, // flag set when unchecked
    MPREF_MAP_HIDE_ACTIVE_VEH_GOTO_PATH = 0x2000000, // flag set when unchecked
};

enum game_diff_level {
    DIFF_CITIZEN = 0,
    DIFF_SPECIALIST = 1,
    DIFF_TALENT = 2,
    DIFF_LIBRARIAN = 3,
    DIFF_THINKER = 4,
    DIFF_TRANSCEND = 5,
};

enum faction_bonus_type {
    FCB_FREETECH = 0,
    FCB_FREEUNIT = 1,
    FCB_FREEFAC = 2,
    FCB_SOCIAL = 3,
    FCB_IMMUNITY = 4,
    FCB_IMPUNITY = 5,
    FCB_PENALTY = 6,
    FCB_FUNGNUTRIENT = 7,
    FCB_FUNGMINERALS = 8,
    FCB_FUNGENERGY = 9,
    FCB_ROBUST = 10,
    FCB_VOTES = 11,
    FCB_FREEFAC_PREQ = 12,
    FCB_REVOLT = 13,
    FCB_NODRONE = 14,
    FCB_FREEABIL_PREQ = 15,
    FCB_PROBECOST = 16,
    FCB_DEFENSE = 17,
    FCB_OFFENSE = 18,
};

enum faction_rule_flags {
    RFLAG_TECHSTEAL = 0x10,
    RFLAG_TECHSHARE = 0x20,
    RFLAG_WORMPOLICE = 0x40,
    RFLAG_ALIEN = 0x80,
    RFLAG_AQUATIC = 0x100,
    RFLAG_FREEPROTO = 0x200,
    RFLAG_FANATIC = 0x400,
    RFLAG_MINDCONTROL = 0x800,
    RFLAG_COMMFREQ = 0x1000,
    RFLAG_TERRAFORM = 0x2000,
    RFLAG_INTEREST = 0x4000,
    RFLAG_MORALE = 0x8000,
};

enum diplo_status {
    DIPLO_PACT = 0x1,
    DIPLO_TREATY = 0x2,
    DIPLO_TRUCE = 0x4,
    DIPLO_COMMLINK = 0x8,
    DIPLO_VENDETTA = 0x10,
    DIPLO_WANT_REVENGE = 0x20,
    DIPLO_UNK_40 = 0x40,
    DIPLO_UNK_80 = 0x80,
    DIPLO_UNK_100 = 0x100,
    DIPLO_UNK_200 = 0x200,
    DIPLO_SHALL_BETRAY = 0x400,
    DIPLO_UNK_800 = 0x800,
    DIPLO_HAVE_INFILTRATOR = 0x1000,
    DIPLO_WANT_TO_TALK = 0x2000,
    DIPLO_UNK_4000 = 0x4000,
    DIPLO_RENEW_INFILTRATOR = 0x8000, // infiltration done on this turn
    DIPLO_UNK_10000 = 0x10000, // "informal" truce status?
    DIPLO_UNK_20000 = 0x20000,
    DIPLO_ATROCITY_VICTIM = 0x40000,
    DIPLO_UNK_80000 = 0x80000,
    DIPLO_UNK_100000 = 0x100000,
    DIPLO_UNK_200000 = 0x200000,
    DIPLO_UNK_400000 = 0x400000,
    DIPLO_UNK_800000 = 0x800000,
    DIPLO_UNK_1000000 = 0x1000000,
    DIPLO_HAVE_SURRENDERED = 0x2000000,
    DIPLO_UNK_4000000 = 0x4000000,
    DIPLO_UNK_8000000 = 0x8000000,
    DIPLO_UNK_10000000 = 0x10000000,
    DIPLO_UNK_20000000 = 0x20000000,
    DIPLO_UNK_40000000 = 0x40000000,
    DIPLO_UNK_80000000 = 0x80000000,
};

enum diplo_agenda {
    AGENDA_UNK_1 = 0x1,
    AGENDA_UNK_2 = 0x2,
    AGENDA_UNK_4 = 0x4,
    AGENDA_FIGHT_TO_DEATH = 0x8,
    AGENDA_UNK_10 = 0x10,
    AGENDA_UNK_20 = 0x20,
    AGENDA_UNK_40 = 0x40,
    AGENDA_UNK_80 = 0x80,
    AGENDA_UNK_100 = 0x100,
    AGENDA_UNK_200 = 0x200,
    AGENDA_UNK_400 = 0x400,
    AGENDA_UNK_800 = 0x800,
    AGENDA_UNK_1000 = 0x1000,
    AGENDA_PERMANENT = 0x2000,
    AGENDA_UNK_4000 = 0x4000,
    AGENDA_UNK_8000 = 0x8000,
};

enum player_flags {
    PLR_SELF_AWARE_COLONY_LOST_MAINT = 0x20, // used to even out lossy integer division
    PLR_MAP_REVEALED = 0x200,
    PLR_GENETIC_PLAGUE_INTRO = 0x400, // +1 to defense against after 1st time faction experiences
    PLR_BEEN_ELECTED_GOVERNOR = 0x8000, // used to determine whether #GOVERNOR has been displayed
    PLR_UNK_10000 = 0x10000,
    PLR_UNK_20000 = 0x20000,
    PLR_STRAT_ATK_ENEMY_HQ = 0x200000,
    PLR_COOP_WITH_HUMAN = 0x400000,
    PLR_TEAM_UP_VS_HUMAN = 0x800000,
    PLR_COMMIT_ATROCIT_WANTONLY = 0x1000000,
    PLR_OBLIT_CAPTURED_BASES = 0x2000000,
    PLR_EMPHASIZE_LAND_POWER = 0x4000000,
    PLR_EMPHASIZE_SEA_POWER = 0x8000000,
    PLR_EMPHASIZE_AIR_POWER = 0x10000000,
    PLR_STRAT_SEARCH_OBJECTIVES = 0x20000000,
    PLR_STRAT_DEF_OBJECTIVES = 0x40000000,
    PLR_STRAT_ATK_OBJECTIVES = 0x80000000,
};

enum player_flags_extended {
    PLR_EXT_STRAT_LOTS_COLONY_PODS = 0x1,
    PLR_EXT_STRAT_LOTS_TERRAFORMERS = 0x2,
    PLR_EXT_STRAT_LOTS_SEA_BASES = 0x4,
    PLR_EXT_STRAT_LOTS_PROBE_TEAMS = 0x8,
    PLR_EXT_STRAT_LOTS_MISSILES = 0x10,
    PLR_EXT_SHAMELESS_BETRAY_HUMANS = 0x20,
    PLR_EXT_STRAT_LOTS_ARTILLERY = 0x40,
};

enum base_state_flags {
    BSTATE_UNK_1 = 0x1,
    BSTATE_DRONE_RIOTS_ACTIVE = 0x2,
    BSTATE_GOLDEN_AGE_ACTIVE = 0x4,
    BSTATE_UNK_20 = 0x20, // enemy_strategy, former units
    BSTATE_RESEARCH_DATA_STOLEN = 0x40,
    BSTATE_GENETIC_PLAGUE_INTRO = 0x20000,
    BSTATE_UNK_80000 = 0x80000, // enemy_strategy, former units
    BSTATE_ENERGY_RESERVES_DRAINED = 0x400000,
    BSTATE_PRODUCTION_DONE = 0x800000,
    BSTATE_UNK_4000000 = 0x4000000, // enemy_strategy
    BSTATE_UNK_8000000 = 0x8000000, // enemy_strategy
    BSTATE_PSI_GATE_USED = 0x20000000,
    BSTATE_HURRY_PRODUCTION = 0x40000000,
};

enum base_event_flags {
    BEVENT_UNK_100 = 0x100,
    BEVENT_BUMPER = 0x200,
    BEVENT_FAMINE = 0x400,
    BEVENT_INDUSTRY = 0x800,
    BEVENT_BUST = 0x1000,
    BEVENT_HEAT_WAVE = 0x2000,
    BEVENT_CLOUD_COVER = 0x4000,
    BEVENT_OBJECTIVE = 0x8000,
};

enum base_governor_flags {
    GOV_MANAGES_PRODUCTION = 0x1,
    // 0x2
    // 0x4
    // 0x8
    // 0x10
    GOV_MAY_HURRY_PRODUCTION = 0x20,
    GOV_MANAGES_CITIZENS_SPECS = 0x40, // incl. drone riots
    GOV_NEW_VEH_FULLY_AUTO = 0x80,
    // 0x100
    GOV_MAY_PROD_LAND_COMBAT = 0x200,
    GOV_MAY_PROD_NAVAL_COMBAT = 0x400,
    GOV_MAY_PROD_AIR_COMBAT = 0x800,
    GOV_MAY_PROD_LAND_DEFENS = 0x1000,
    GOV_MAY_PROD_AIR_DEFENS = 0x2000,
    // 0x4000 ; Naval defense?
    GOV_MAY_PROD_TERRAFORMS = 0x8000,
    GOV_MAY_PROD_FACILITIES = 0x10000,
    GOV_MAY_PROD_COLONY_POD = 0x20000,
    GOV_MAY_PROD_SP = 0x40000,
    GOV_MAY_PROD_PROTOTYPE = 0x80000,
    GOV_MAY_PROD_PROBES = 0x100000,
    GOV_MULTI_PRIORITIES = 0x200000, // or no priorities
    GOV_MAY_PROD_EXPLR_VEH = 0x400000, // scout/exploration units
    GOV_MAY_PROD_TRANSPORT = 0x800000,
    GOV_PRIORITY_EXPLORE = 0x1000000,
    GOV_PRIORITY_DISCOVER = 0x2000000,
    GOV_PRIORITY_BUILD = 0x4000000,
    GOV_PRIORITY_CONQUER = 0x8000000,
    // 0x10000000
    // 0x20000000
    GOV_UNK_40000000 = 0x40000000,
    GOV_ACTIVE = 0x80000000,
};

enum MapItem {
    BIT_BASE_IN_TILE = 0x1,
    BIT_UNIT_IN_TILE = 0x2,
    BIT_ROAD = 0x4,
    BIT_MAGTUBE = 0x8,
    BIT_MINE = 0x10,
    BIT_FUNGUS = 0x20,
    BIT_SOLAR = 0x40,
    BIT_RIVER = 0x80,
    BIT_RIVER_SRC = 0x100, // River begins here for visual effect
    BIT_RIVER_LAKE = 0x200, // Shows more water for visual effect
    BIT_BONUS_RES = 0x400,
    BIT_BUNKER = 0x800,
    BIT_BASE_RADIUS = 0x1000, // Production radius; 21 tiles per base
    BIT_MONOLITH = 0x2000,
    BIT_CANAL_COAST = 0x4000, // Land continent (this tile) + 1-tile canal + another continent.
    // Both regions must also meet certain tile count threshold.
    BIT_FARM = 0x8000,
    BIT_ENERGY_RES = 0x10000,
    BIT_MINERAL_RES = 0x20000,
    BIT_AIRBASE = 0x40000,
    BIT_SOIL_ENRICHER = 0x80000,
    BIT_SUPPLY_REMOVE = 0x100000, // Prevent randomly generated pods from appearing here
    BIT_FOREST = 0x200000,
    BIT_CONDENSER = 0x400000,
    BIT_ECH_MIRROR = 0x800000,
    BIT_THERMAL_BORE = 0x1000000,
    BIT_UNK_2000000 = 0x2000000, // related to monoliths, maybe redundant
    BIT_UNK_4000000 = 0x4000000, // this tile has a pod when no unity scattering
    BIT_UNK_8000000 = 0x8000000, // this tile has a pod when no unity scattering
    BIT_SUPPLY_POD = 0x10000000,
    BIT_NUTRIENT_RES = 0x20000000,
    BIT_DOUBLE_SEA = 0x40000000, // Iterate adjacent 8 sea tiles, set bit if there are
    // more than one group of sea tiles separated by land tiles, can be same sea region.
    BIT_SENSOR = 0x80000000,
};

const uint32_t TerraformRules[20][2] = { // terrain enhancement, incompatible on same tile
    BIT_FARM,          BIT_FOREST, // farm
    BIT_SOIL_ENRICHER, BIT_FOREST, // soil enricher
    BIT_MINE,          BIT_MINE | BIT_SOLAR | BIT_FOREST | BIT_CONDENSER | BIT_ECH_MIRROR
                       | BIT_THERMAL_BORE | BIT_SENSOR, // mine
    BIT_SOLAR,         BIT_MINE | BIT_SOLAR | BIT_FOREST | BIT_CONDENSER | BIT_ECH_MIRROR
                       | BIT_THERMAL_BORE | BIT_SENSOR, // solar collector / tidal harness
    BIT_FOREST,        BIT_MINE | BIT_FUNGUS | BIT_SOLAR | BIT_FARM | BIT_SOIL_ENRICHER
                       | BIT_FOREST | BIT_CONDENSER | BIT_ECH_MIRROR | BIT_THERMAL_BORE, // forest
    BIT_ROAD,          0, // road
    BIT_MAGTUBE,       0, // magtube
    BIT_BUNKER,        BIT_AIRBASE, // bunker
    BIT_AIRBASE,       BIT_BUNKER, // airbase
    BIT_SENSOR,        BIT_MINE | BIT_SOLAR | BIT_CONDENSER | BIT_ECH_MIRROR
                       | BIT_THERMAL_BORE, // sensor
    0,                 BIT_FUNGUS, // fungus remove
    BIT_FUNGUS,        BIT_MINE | BIT_SOLAR | BIT_FARM | BIT_SOIL_ENRICHER
                       | BIT_FOREST, // fungus plant
    BIT_CONDENSER,     BIT_MINE | BIT_SOLAR | BIT_FOREST | BIT_CONDENSER | BIT_ECH_MIRROR
                       | BIT_THERMAL_BORE | BIT_SENSOR, // condenser
    BIT_ECH_MIRROR,    BIT_MINE | BIT_SOLAR | BIT_FOREST | BIT_CONDENSER | BIT_ECH_MIRROR
                       | BIT_THERMAL_BORE | BIT_SENSOR, // echelon mirror
    BIT_THERMAL_BORE,  BIT_MINE | BIT_SOLAR | BIT_FARM | BIT_FOREST | BIT_CONDENSER
                       | BIT_ECH_MIRROR | BIT_THERMAL_BORE | BIT_SENSOR, // thermal borehole
    0,                 0, // aquifer
    0,                 0, // raise land
    0,                 0, // lower land
    0,                 0, // level terrain
    BIT_MONOLITH,      BIT_SUPPLY_POD | BIT_NUTRIENT_RES | BIT_BONUS_RES, // monolith
};

enum MapLandmark {
    LM_CRATER = 0x1,
    LM_VOLCANO = 0x2,
    LM_JUNGLE = 0x4,
    LM_URANIUM = 0x8,
    LM_SARGASSO = 0x10,
    LM_RUINS = 0x20,
    LM_DUNES = 0x40,
    LM_FRESH = 0x80,
    LM_MESA = 0x100,
    LM_CANYON = 0x200,
    LM_GEOTHERMAL = 0x400,
    LM_RIDGE = 0x800,
    LM_BOREHOLE = 0x1000,
    LM_NEXUS = 0x2000,
    LM_UNITY = 0x4000,
    LM_FOSSIL = 0x8000,
};

enum VehOrder {
    ORDER_NONE = 0,              //  -
    ORDER_SENTRY_BOARD = 1,      // (L)
    ORDER_HOLD = 2,              // (H); Hold (set 1st waypoint (-1, 0)), Hold 10 (-1, 10), On Alert
    ORDER_CONVOY = 3,            // (O)
    ORDER_FARM = 4,              // (f)
    ORDER_SOIL_ENRICHER = 5,     // (f)
    ORDER_MINE = 6,              // (M)
    ORDER_SOLAR_COLLECTOR = 7,   // (S)
    ORDER_PLANT_FOREST = 8,      // (F)
    ORDER_ROAD = 9,              // (R)
    ORDER_MAGTUBE = 10,          // (R)
    ORDER_BUNKER = 11,           // (K)
    ORDER_AIRBASE = 12,          // (.)
    ORDER_SENSOR_ARRAY = 13,     // (O)
    ORDER_REMOVE_FUNGUS = 14,    // (F)
    ORDER_PLANT_FUNGUS = 15,     // (F)
    ORDER_CONDENSER = 16,        // (N)
    ORDER_ECHELON_MIRROR = 17,   // (E)
    ORDER_THERMAL_BOREHOLE = 18, // (B)
    ORDER_DRILL_AQUIFER = 19,    // (Q)
    ORDER_TERRAFORM_UP = 20,     // (])
    ORDER_TERRAFORM_DOWN = 21,   // ([)
    ORDER_TERRAFORM_LEVEL = 22,  // (_)
    ORDER_PLACE_MONOLITH = 23,   // (?)
    ORDER_MOVE_TO = 24,          // (G); Move unit to here, Go to Base, Group go to, Patrol
    ORDER_MOVE = 25,             // (>); Only used in a few places, seems to be buggy mechanic
    ORDER_EXPLORE = 26,          // (/); not set via shortcut, AI related?
    ORDER_ROAD_TO = 27,          // (r)
    ORDER_MAGTUBE_TO = 28,       // (t)
    ORDER_AI_GO_TO = 88,         //  - ; ORDER_GO_TO (0x18) | 0x40 > 0x58 ? only used by AI funcs
};

enum FormerItem {
    FORMER_NONE = -1, // Thinker variable
    FORMER_FARM = 0,
    FORMER_SOIL_ENR = 1,
    FORMER_MINE = 2,
    FORMER_SOLAR = 3,
    FORMER_FOREST = 4,
    FORMER_ROAD = 5,
    FORMER_MAGTUBE = 6,
    FORMER_BUNKER = 7,
    FORMER_AIRBASE = 8,
    FORMER_SENSOR = 9,
    FORMER_REMOVE_FUNGUS = 10,
    FORMER_PLANT_FUNGUS = 11,
    FORMER_CONDENSER = 12,
    FORMER_ECH_MIRROR = 13,
    FORMER_THERMAL_BORE = 14,
    FORMER_AQUIFER = 15,
    FORMER_RAISE_LAND = 16,
    FORMER_LOWER_LAND = 17,
    FORMER_LEVEL_TERRAIN = 18,
    FORMER_MONOLITH = 19,
};

enum terrain_altitude {
    ALT_OCEAN_TRENCH = 0,
    ALT_OCEAN = 1,
    ALT_OCEAN_SHELF = 2,
    ALT_SHORE_LINE = 3,
    ALT_ONE_ABOVE_SEA = 4,
    ALT_TWO_ABOVE_SEA = 5,
    ALT_THREE_ABOVE_SEA = 6,
    ALT_FOUR_ABOVE_SEA = 7,
};

enum terrain_basic_flags {
    TILE_MOIST = 0x8,
    TILE_RAINY = 0x10,
    TILE_ROLLING = 0x40,
    TILE_ROCKY = 0x80,
};

enum AIGoal {
    AI_GOAL_UNUSED = -1,
    AI_GOAL_ATTACK = 0, // 'a', red
    AI_GOAL_DEFEND = 2, // 'd', yellow
    AI_GOAL_SCOUT = 3, // 's', pink
    AI_GOAL_UNK_1 = 6, // 'n', blue ; related to tile visibility
    AI_GOAL_UNK_2 = 7, // related to movement
    AI_GOAL_COLONIZE = 8, // 'c', teal
    AI_GOAL_TERRAFORM_LAND = 9, // 'f', green ' ;
    AI_GOAL_UNK_3 = 11, // related to combat
    AI_GOAL_ECHELON_MIRROR = 13,
    AI_GOAL_PRIORITY_COMBAT = 16, // possibly artillery related
    AI_GOAL_TERRAFORM_WATER = 25,
    AI_GOAL_UNK_4 = 41, // '^', white
    AI_GOAL_CONDENSER = 73,
    AI_GOAL_THERMAL_BOREHOLE = 105,
    AI_GOAL_SENSOR_ARRAY = 121,
    // Thinker goals start here
    AI_GOAL_RAISE_LAND = 200,
    AI_GOAL_NAVAL_START = 201,
    AI_GOAL_NAVAL_END = 202,
    AI_GOAL_NAVAL_BEACH = 203,
    AI_GOAL_NAVAL_SCOUT = 204,
    Thinker_Goal_ID_First = AI_GOAL_RAISE_LAND,
};

enum social_category_types {
    SOCIAL_C_POLITICS = 0,
    SOCIAL_C_ECONOMICS = 1,
    SOCIAL_C_VALUES = 2,
    SOCIAL_C_FUTURE = 3,
};

enum social_model_types {
    SOCIAL_M_FRONTIER = 0,
    SOCIAL_M_POLICE_STATE = 1,
    SOCIAL_M_DEMOCRATIC = 2,
    SOCIAL_M_FUNDAMENTALIST = 3,

    SOCIAL_M_SIMPLE = 0,
    SOCIAL_M_FREE_MARKET = 1,
    SOCIAL_M_PLANNED = 2,
    SOCIAL_M_GREEN = 3,

    SOCIAL_M_SURVIVAL = 0,
    SOCIAL_M_POWER = 1,
    SOCIAL_M_KNOWLEDGE = 2,
    SOCIAL_M_WEALTH = 3,

    SOCIAL_M_NONE = 0,
    SOCIAL_M_CYBERNETIC = 1,
    SOCIAL_M_EUDAIMONIC = 2,
    SOCIAL_M_THOUGHT_CONTROL = 3,
};

enum mapwin_state {
    MAPWIN_DRAW_TRANSLUCENT = 0x2, // render translucent sprites, farms/forests excl. fungus
    MAPWIN_DRAW_SITES = 0x4, // debug overlay
    MAPWIN_UNK_10 = 0x10, // render some random yellow sprites
    MAPWIN_DRAW_IMPROVEMENTS = 0x20, // render terrain improvements
    MAPWIN_DRAW_UNITS = 0x40,
    MAPWIN_DRAW_BASE_TILES = 0x80,
    MAPWIN_DRAW_BONUS_RES = 0x200, // render supply pods, bonus resources, landmarks
    MAPWIN_DRAW_RIVERS = 0x400,
    MAPWIN_DRAW_BASE_NAMES = 0x800,
    MAPWIN_HIDE_UNITS_BASES = 0x1000, // hide units/base tiles
    MAPWIN_DRAW_GOALS = 0x2000, // debug overlay
    MAPWIN_UNK_4000 = 0x4000, // zeros in almost every tile
    MAPWIN_DRAW_BORDERS = 0x10000,
    MAPWIN_DRAW_CURSOR_COMPASS = 0x20000,
    MAPWIN_DRAW_DIPLO_STATE = 0x100000, // show faction treaty status matrix in window corner
    MAPWIN_DRAW_SOLID_RADIUS = 0x1000000, // faction base radius solid color terrain view
    MAPWIN_HIDE_OCEAN_BASE = 0x2000000, // stop rendering ocean base layer
    MAPWIN_HIDE_TERRAIN = 0x10000000, // stop rendering all terrain
    MAPWIN_DRAW_SOLID_BORDERS = 0x80000000, // faction borders solid color terrain view
};

