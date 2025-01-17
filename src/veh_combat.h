#pragma once

#include "main.h"

int __cdecl fungal_tower_bonus(int value);
int __cdecl dream_twister_bonus(int value);
int __cdecl neural_amplifier_bonus(int value);
int __cdecl psi_factor(int value, int faction_id, bool is_attack, bool is_fungal_twr);

int __cdecl mod_morale_alien(int veh_id, int faction_id_vs_native);
int __cdecl mod_morale_veh(int veh_id, bool check_drone_riot, int faction_id_vs_native);
int __cdecl mod_get_basic_offense(int veh_id_atk, int veh_id_def, int psi_combat_type, bool is_bombard, bool unk_tgl);
int __cdecl mod_get_basic_defense(int veh_id_def, int veh_id_atk, int psi_combat_type, bool is_bombard);

int __cdecl mod_best_defender(int veh_id_def, int veh_id_atk, bool check_arty);
int __cdecl battle_fight_parse_num(int index, int value);

