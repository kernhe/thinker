#pragma once

#include "main.h"

typedef int PMTable[MaxMapW][MaxMapH];

const int BASE_DISALLOWED = (BIT_BASE_IN_TILE | BIT_MONOLITH | BIT_FUNGUS | BIT_THERMAL_BORE);

extern PMTable pm_target;
extern PMTable pm_overlay;

int __cdecl mod_enemy_move(const int id);
int __cdecl log_veh_kill(int a, int b, int c, int d);
int ocean_coast_tiles(int x, int y);
void update_main_region(int faction);
void move_upkeep(int faction, bool visual);
void land_raise_plan(int faction, bool visual);
bool has_transport(int x, int y, int faction);
bool allow_move(int x, int y, int faction, int triad);
bool non_combat_move(int x, int y, int faction, int triad);
bool can_build_base(int x, int y, int faction, int triad);
bool has_base_sites(int x, int y, int faction, int triad);
int select_item(int x, int y, int faction, MAP* sq);
int crawler_move(const int id);
int colony_move(const int id);
int former_move(const int id);
int trans_move(const int id);
int aircraft_move(const int id);
int combat_move(const int id);

