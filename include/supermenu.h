#ifndef supermenu_h
#define supermenu_h

#include "./UI.h"

/** @brief Indexing for Supermenu::Sel */
typedef enum eSuperMenu {
	/** @brief aka new game */
	eSuperMenu_BACK,
	eSuperMenu_SAVE,
	eSuperMenu_LOAD,
	eSuperMenu_QUIT,
	eSuperMenu_LEN
} eSuperMenu;

/** @brief 
 * The menu which could pop up whenever.
 *
 * - New Game (or Back to game)
 * - Save
 * - Load
 * - Exit
 * */
typedef struct SuperMenu {
	eSuperMenu cursor;
	eUILocs last;
} SuperMenu;

#endif
