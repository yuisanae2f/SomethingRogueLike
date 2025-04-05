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
 *
 * Every variables - even temporaries would be in this structure
 * so this would have the enough power to represent itself as a whole game,
 * and the game's state.
 *
 * It is meant to be initiated as zero.
 * */
typedef struct Game {
	Battle battle;
	UI* ui;

	/** @brief aka is the game just started now? */
	bool hastutorialpassed;

	/** 
	 * @brief
	 * Component for UI.
	 * It will load UI depends on the Game::ui's state.
	 * */
	UIComponent com;

	eUILocs 
		/**
		 * @brief
		 * This shows which state is in `Game`.
		 * */
		loc,

		/**
		 * @brief
		 * The location when "Go back" on supermenu triggers.
		 * */
		loclast,

		/**
		 * @brief Destination variable given for `PATHFINDER`. 
		 * */
		locdest;



	/** Gesture, or input for Game::ui */
	UIGesture_t gest;
	
	union {
		/** 
		 * @brief
		 * cursor for supermenu::saveload
		 *
		 * @details
		 * 0: FILE 0
		 * 1: FILE 1
		 * 2: FILE 2
		 * 3: Go back to the menu
		 * */
		UIFilec_t saveload;

		/** @brief 
		 * # Super Menu  
		 * The menu which could pop up whenever.
		 * - New Game (or Back to game)
		 * - Save
		 * - Load
		 * - Exit
		 * */
		eSuperMenu_t smenu;

		/**
		 * @brief
		 * First sector will be full for indexer of one team of yours. \n
		 * Last-1 of it will try to open inventory, which is shared for one team.
		 * Last of it will let you to TITIL.
		 * */
		unsigned char battle;
	}
	/** 
	 * @brief 
	 * Cursor, which will decide which part are you watching at. 
	 *
	 * Context and needed size would be various.
	 * Each of them do not interact each other.
	 * Each cursor must be temporary.
	 * */
	cursor;
} Game;

#endif
