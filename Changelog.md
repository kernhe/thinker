
# Thinker mod release changelog

## Version 2.6 (2021-05-01)
* New option: skip_faction will exclude some factions from random selection in the game setup.
* New option: conquer_priority provides ability to tweak the AI affinity to build more military units.
* Bases that are about to drone riot on the next turn are now highlighted with a red label on the world map.
* Game now preserves autosave files for each turn in the saves folder. They are overwritten only when the turn is played again.
* Release now contains German translation for alphax.txt provided by Pianoslum.
* Add more checks for AI base production to avoid building too expensive facilities.
* AI can now build additional mineral multiplier facilities in one base. However this can only happen if it doesn't push the base over eco damage threshold.
* AI sometimes builds Punishment Spheres in captured bases.
* AI formers will occasionally drill new rivers.
* AI tries to determine better if it needs land or sea former units.
* AI sometimes does naval landings on the same continent when the distance is shorter than land route.
* More additional tweaks to AI unit movement and scouting priorities.
* Fix game showing redundant "rainfall patterns have been altered" messages when these events are caused by other factions.
* Fix AI not attacking certain aircraft in flight even when it had the chance to do so.
* Fix AI building too many conventional missiles or obsolete planet busters under certain conditions.
* Fix AI not starting to build Ascent to Transcendence when Voice of Planet is operational.


## Version 2.5 (2021-04-11)
* Add new in game menu support for Thinker features (ALT+T shortcut). While a game is loaded, the menu will display elapsed time during that savegame.
* Add menu option to toggle world_map_labels while in game.
* Bases that have Flechette Defense System or Geo Survey Pods are now highlighted with a blue label on the world map.
* Many adjustments to combat movement logic. AI tries to distribute attackers to many more tiles to avoid collateral damage.
* Improve AI pathfinding to take into account 1-tile chokepoints that are occupied by a base.
* AI costs in revised_tech_cost can now be set separately with tech_cost_factor option.
* Rename expansion_factor option to expansion_limit. It is now a fixed limit for all map sizes.
* Replace ignore_reactor_power patch with Will To Power version. This implementation does not require any changes to script.txt and will display combat odds in the vanilla format.
* AI base spacing can now be adjusted with base_spacing and base_nearby_limit options. By default they are the same values than previous versions.
* Add new options: expansion_autoscale, social_ai_bias, new_base_names, disable_alien_guaranteed_techs and player_free_units.
* AI adjusts satellite production amounts automatically based on population levels if it is below satellite_limit option.
* AI takes facility cost and maintenance now better into account in production choices.
* AI tries to build Geo Survey Pods in a way that they achieve better uniform coverage across territory.
* AI builds more colony pods to expand faster if there is a lot of space available.
* In the early game, AI tries to determine more accurately if it needs more scout units.
* Reduce crawler production slightly if the bases are already close together.


## Version 2.4 (2021-03-14)
* Add config options to choose if the Planet should randomly spawn expansion-only units. This works even if smac_only is not selected.
* Add many new config options for unit repair rates. This is the same implementation than in Will To Power.
* Unit repair rates have been reduced from standard values. In particular, Command Centers and similar facilities heal only 20% per turn.
* Bases in golden age are now highlighted with a colored label on the world map. This can be toggled with world_map_labels config option.
* Config options for social_ai have been expanded.
* Many general improvements to AI combat movement logic to take into account more factors.
* AI tries to avoid probing enemy factions that have the Hunter Seeker Algorithm.
* AI is updated to sometimes choose a wider variety of naval invasion locations.
* Fix issue where AI wasted Choppers because of fuel exhaustion.
* Fix bug with design_units that caused some AI prototypes to become corrupted in the savegame. The fix automatically prunes incorrect prototypes from the savegame while processing next turn change.


## Version 2.3 (2020-12-27)
* New option: cpu_idle_fix lowers the processing power consumption to a minimum by throttling unnecessary code. This uses the same method than smac-cpu-fix patch.
* New option: rare_supply_pods will reduce the frequency of supply pods to around one third of previous levels and instead places bonus resources on random maps. This option is a lesser version of "no unity scattering".
* New option: smooth_scrolling (disabled by default) adds support for some user interface enhancements provided by PlotinusRedux's PRACX mod.
* New option: windowed adds support to run the game using a user-supplied resolution. Command line option -windowed is also supported.
* Config file now includes options to set the display mode for the game. DirectDraw / DisableOpeningMovie options will override any values in Alpha Centauri.ini.
* By default the game starts now in native desktop resolution. Opening movie will also be skipped by default.
* Thinker now controls the movement of nearly all combat units, with the only major exception being missile units that are managed by the vanilla AI code.
* AI garrisoning priorities are rewritten to move defending units to bases that are the most threatened.
* Add AI planning capability to execute naval invasions over long distances with multiple transports using other combat ships as cover.
* Combat ships will now engage other targets with artillery much more often instead of always defaulting to normal direct attack.
* All artillery units will use new targeting logic to place them in more useful positions and prioritize threats more accurately.
* AI will occasionally use Drop Pods ability to deploy troops to other bases.
* Foil probe teams will now also attack coastal bases instead of only sea bases like previously.
* Changed territory_border_fix to increase the expansion of coastal base territory into ocean to an equal amount of actual sea bases.
* New feature: ALT+T shortcut displays general statistics about the factions.
* New feature: the game engine has a crash handler provided by Thinker that writes output to debug.txt if the game happens to crash for any reason.
* Set config option ignore_reactor_power enabled by default. This is non-vanilla but a much needed balance fix.
* AI tries to leave slightly more space between bases and prioritize locating bases on the ocean coastline.
* AI should build Tree Farms faster if the bases encounter eco damage unless the faction file has a negative PLANET modifier.
* AI will now attempt to raise land bridges between continents more often using better pathing. These goals are also stored in the save game.
* AI will occasionally disband formers or colony pods if there's no use for them.


## Version 2.2 (2020-11-15)
* New option: clean_minerals sets the amount of minerals a base can produce before experiencing eco damage.
* Improve rendering on ocean fungus tiles where they now display consistent graphics compared to the adjacent land fungus tiles.
* Game now displays a warning on startup if an unknown config option is detected in thinker.ini.
* Fix issue where revised_tech_cost was not working in the previous version.
* Fix engine bug where selecting bombardment on an empty square sometimes resulted in the attacking unit being destroyed.
* Fix very rare issue where a faction might get eliminated even when they had active colony pods.


## Version 2.1 (2020-11-08)
* New option: ignore_reactor_power (disabled by default). This makes the combat calculation ignore reactor power and treat every unit as having a fission reactor. Combat odds are also properly displayed in the confirmation dialog. More advanced reactors still provide their usual cost discounts. Planet busters are unaffected by this feature.
* New option: territory_border_fix will make the oldest bases claim tiles that are equidistant between two bases of different factions. Coastal bases also expand territory into the ocean for each of the 20 workable tiles in the base radius.
* Addition to eco_damage_fix: clean minerals cap will now increase every time Tree Farm, Hybrid Forest, Centauri Preserve or Temple of Planet is built even if no fungal pop has been encountered yet. It is not necessary anymore to delay building these facilities to alleviate eco damage.
* Faction placement is improved on custom maps where some starting locations were not previously picked.
* AI production planner tries to avoid building certain secret projects if they yield only marginal benefits.
* Include also TALENT and ROBUST modifiers in social_ai calculation.
* Fix issue where alien factions didn't gain the bonuses provided by free_colony_pods or free_formers.
* Fix issue where governors didn't sometimes work in player-owned bases.
* Fix AI vehicle home base reassignment bug where an apparent oversight made the game engine to reassign vehicles to bases with mineral_surplus < 2. Credits: Will To Power mod.


## Version 2.0 (2020-05-31)
* Road building algorithm has been completely rewritten to build more natural looking road networks.
* AI will now build magtubes after the tech is acquired.
* Draw a visual marker around the population label of HQ bases to identify them more easily.
* Tech costs in revised_tech_cost formula towards the late game are increased. Techs in the lower tiers are slightly cheaper than before.
* AI research bonuses in revised_tech_cost have been significantly reduced.
* Remove the mechanic where the first 10 techs are cheaper.
* Adjust the mod to calculate Social Engineering research effect similarly to vanilla game.
* AI prototype selection formula has been revamped to take into account more factors and to avoid selecting units that would take too long to produce.
* Adjust the AI logic whether to build conventional or PSI units. AI now takes into account if the faction has Worm Police ability.
* AI now attempts to design various units equipped with the Trance ability.
* AI sometimes builds Tachyon Fields, Geosynchronous Survey Pods and Flechette Defense Systems.
* Reduce overall sea level rise frequency to 1/3.
* Add Trance Scout Patrol and Police Garrison predefined units.
* Add proper parsing for special scenario rules: No terraforming, No colony pods can be built and No secret projects can be built.
* Add better handling for cases where the global unit count is nearing the limit (2048) and make the AI build facilities instead. If no suitable facilities are available, AI will switch production to Stockpile Energy.
* Add meaningful error message dialogs if some of the startup checks for Thinker fail.
* Import the following patches from Will To Power mod by tnevolin: collateral_damage_value, disable_planetpearls, disable_aquatic_bonus_minerals. Each of them also has their own config option.
* New option: auto_relocate_hq will automatically move lost HQs to another suitable base.
* New option: eco_damage_fix will equalize the eco damage between player and AI bases.
* New option: content_pop_player/content_pop_computer will adjust the default number of content population in each base.
* New option: free_colony_pods can be used to spawn extra units for the computer factions.
* Fix issue where AI might build Voice of Planet even if Transcendence victory condition was disabled.
* Fix issue where AI bases sometimes persist without any defenders. AI will now force switch production away from facilities if no valid defenders are present.
* Fix a bug where attacking other satellites didn't work in Orbital Attack View when smac_only was activated. Credits: Scient.
* Fix engine bug where a faction with enough energy credits would attempt to Corner Energy Market every turn. Now the AI properly only attempts it once and waits for the countdown to complete.


## Version 1.0 (2019-12-12)
* SMAC in SMACX mod files are now included with Thinker by default (can be enabled with smac_only=1)
* Removed smac_only dependency for ac_mod/labels.txt (redundant file for the mod)
* Factions with positive Planet rating will build less boreholes than the average
* Adjust tech_balance feature to also prioritize probe team prerequisite tech
* AI should relocate lost HQs faster than previously
* New option: revised_tech_cost provides an extensive overhaul for the research cost mechanics. More info in Details.md.
* New option: expansion_factor limits how many bases the AI will attempt to build before stopping expansion entirely
* New option: limit_project_start determines how soon the AIs are allowed to start secret projects
* Fix issue where AI sometimes ignored undefended enemy bases when it had the chance to capture them


## Version 0.9 (2019-04-07)
* Thinker now supports formers based on all triads: design_units will also create gravship formers when the techs are available
* AI formers build less roads and other smaller tweaks to former priorities
* AI sometimes nerve staples bases after UN charter has been repealed
* Military unit production priority is notably increased from previous amounts
* Whenever AI loses bases to conquest, this also triggers an extra priority to devote more resources to building new units
* Tech balance prioritizes more early economic techs to ensure important items are not skipped
* Rebalancing of social_ai logic to match faction priorities more closely
* Alphax.txt included in releases to provide optional changes
* Trance ability removed from design_units created probe teams
* Major adjustments to faction placement to improve starting locations
* Possibility to select custom factions in smac_only mod
* Added command line parameter "-smac" to start smac_only mod
* New option: nutrient_bonus for use with faction placement
* New option: hurry_items allows AI to use energy reserves to hurry production (excluding secret projects)
* New option: cost_factor allows one to change AI production bonuses
* New option: max_satellites specifies how many of them AI will build normally
* Fix spawning issues on Map of Planet
* Fix sea bases sometimes not building enough transports
* Fix colony pods freezing in place or being unable to reach their destinations
* Fix stuff being built on volcanoes
* Fix smac_only showing the expansion opening movie
* Fix custom prototypes having incomplete names


## Version 0.8 (2018-11-30)
* New combat logic for land-based units attempts to do counter attacks more often
* New code for selecting social engineering priorities
* AI understands the value of fungus and will sometimes plant it
* AI sometimes builds native units when the psi bonuses are high enough
* Faction placement option added: avoid bad spawns on tiny islands and equalize distances to neighbors
* Landmark selection options added to config
* Experimental load_expansion option added
* Fix secret project movies sometimes not being shown
* Scient patch updated to v2.0


## Version 0.7 (2018-10-03)
* Land-based former code rewritten
* Formers will attempt to raise land bridges to nearby islands
* Crawler code improved to choose better tiles
* Prototype picker values fast units and useful special abilities more
* Design_units configuration option added. Produces improved probe teams and AAA garrisons.
* AI produces now planet busters. Amount depends on the UN charter status and aggressiveness settings.
* AI prioritizes secret projects that match their interests
* AI builds secret projects now in their top third mineral output bases
* Tech requirements now fully moddable in alphax.txt
* Governors of all factions will use more borehole tiles
* Scient patch v1.0 added


## Version 0.6 (2018-08-18)
* First Github release
