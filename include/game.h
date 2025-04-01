#ifndef game_h
#define game_h

#include "./battle.h"
#include "./UI.h"
#include "./supermenu.h"

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
