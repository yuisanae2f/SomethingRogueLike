#ifndef game_h
#define game_h

#include "./battle.h"
#include "./UI.h"
#include "./supermenu.h"

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

	/** @brief 
	 * Your turn ID which is given.
	 * 0 means it is your turn.
	 * */
	battle_teamc_t turnID;

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



	/** @brief Gesture, or input for Game::ui */
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
		 *
		 * @todo
		 * Define its custom type in order to make it flexible
		 * */
		eSuperMenu_t smenu;

		/**
		 * @brief
		 * First sector will be full for indexer of one team of yours. \n
		 * Last-1 of it will try to open inventory, which is shared for one team.
		 * Last of it will let you to TITIL.
		 *
		 * @todo
		 * Define its custom type in order to make it flexible
		 * */
		unsigned char battle;

		/**
		 * @brief
		 * Cursor for the dialog so it could show them where they should see.
		 * It is like a progress bar.
		 *
		 * @todo
		 * Define its custom type in order to make it flexible.
		 * */
		cursor_battle_out_t battle_output;
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

	/** @brief Selected fighter on BATTLE. */
	battle_fighterc_t fighter;

} Game;

#endif
