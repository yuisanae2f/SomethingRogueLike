#ifndef game_h
#define game_h

#include "./battle.h"
#include "./UI.h"
#include "./supermenu.h"

typedef BATTLE_TEAMC_T battle_teamc_t;
typedef struct Battle Battle;

/** @brief 
 * Game itself. 
 * Contains all logic for game.
 * */
typedef struct Game {
	battle_teamc_t whoareyou;
	Battle battle;
	SuperMenu supermenu;
	UI* ui;
} Game;

#endif
