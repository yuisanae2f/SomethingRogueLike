/**
 * @brief
 * Has everything about battle.
 * */

#ifndef battle_h
#define battle_h

#include "./battle.auto.h"
#include "./unit.h"
#include "./ArrLike.h"
#include <time.h>
#include <stdbool.h>

/** @brief Battle Fighter Counter Type */
typedef BATTLE_FIGHTERC_T battle_fighterc_t;

/** @brief Fighters vector */
typedef Unit battle_fighterv_t[BATTLE_FIGHTER_MAX];

/** @brief battle team count */
typedef BATTLE_TEAMC_T battle_teamc_t;

/** 
 * One team as vector. \n
 * It is `ListLike`.
 * */
typedef struct Battle_Team {
	// vector, fighters.
	battle_fighterv_t v;

	// count
	battle_fighterc_t c;

	ArrLikeInjection(
			, Unit
			, battle_fighterc_t
			);

	Inv inv;
} Battle_Team;



/** @brief battle team vector */
typedef Battle_Team battle_teamv_t[BATTLE_TEAM_MAX];

/** @brief Contains all about battle. */
typedef struct Battle {
	/** @brief vector, team */
	battle_teamv_t v;

	battle_teamc_t 
		/** @brief team count */
		c, 
		/** @brief whose turn is it */
		turn;

	ArrLikeInjection(
			, Battle_Team
			, battle_teamc_t
			);

	/**
	 * @brief
	 * ui(showers, like output) for selections.
	 * size is 2.
	 * */
	UISel* uisel;

	/**
	 * @brief
	 * Cursor. \n
	 * 0: Team
	 * 1: Inventory
	 * */
	bool uicursor;

	/**
	 * @brief
	 * UI for Unit.
	 * size is maximum.
	 * */
	UIUnit* uiunit;
} Battle;

/**
 * @brief 
 * Load Battle. \n
 * Available on `BATTLE`. \n
 * This function is is initiator.
 *
 * Verifies Selection UI for Battle.
 *
 * Outputs:
 * - Log
 * - 
 *
 * Selections:
 * - SUPERMENU
 * - INV
 *
 * Needed:
 * - UISelBattleMk
 * - UIInit
 * */
ae2f_extern ae2f_SHAREDCALL
err_t BattleInit(Battle*, UI*);

#endif
