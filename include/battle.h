/**
 * @brief
 * Has everything about battle.
 * */

#ifndef battle_h
#define battle_h

#include "./battle.auto.h"
#include "./unit.h"
#include "./ArrLike.h"
#include <stdbool.h>

/** @brief Battle Fighter Counter Type */
typedef BATTLE_FIGHTERC_T battle_fighterc_t;

/** @brief Fighters vector */
typedef Unit battle_fighterv_t[BATTLE_FIGHTER_MAX];

/** @brief battle team count */
typedef BATTLE_TEAMC_T battle_teamc_t;

/** @brief Cursor type for battle output (Like a progress bar) */
typedef CURSOR_BATTLE_OUT_T cursor_battle_out_t;

/** 
 * One team as vector. \n
 * It is `ListLike`.
 * */
typedef struct Battle_Team {
	/** @brief Battlers array */
	battle_fighterv_t v;

	/** @brief Battler count  */
	battle_fighterc_t c;

	ArrLikeInjection(
			, Unit
			, battle_fighterc_t
			);

	/** @brief Inventory */
	Inv inv;
} Battle_Team;



/** @brief battle team vector */
typedef Battle_Team battle_teamv_t[BATTLE_TEAM_MAX];

typedef struct UIND	UIND;
typedef struct UISel	UISel;

/** 
 * @brief 
 * Contains all about battle.
 *
 * Treated as a plain data: 
 * which means it must not contain any logic, including any pointers.
 * 
 * So we could have no difficulty for saving on minimal version, by just like fread, fwrite. 
 * */
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

	struct {
		/** @brief Opposite's team */
		battle_teamc_t oteam;

		battle_fighterc_t
			/** @brief 
			 * Selected fighter on BATTLE. 
			 * Its turn equals to Battle::turn
			 * */
			ifighter

			/** @brief For opposite's team */
			, ofighter;
	} ActCommand; /** @brief Target finding index for ActQueued. */


	/** @brief Act which is queued; */
	eActs_t ActQueued;

	/**
	 * @brief
	 * Cursor for the dialog so it could show them where they should see.
	 * It is like a progress bar.
	 *
	 * @todo
	 * Define its custom type in order to make it flexible.
	 * */
	cursor_battle_out_t act_idx;

} Battle;

#endif
