#ifndef act_h
#define act_h

#include "./battle.auto.h"
#include "./err.h"
#include <ae2f/Call.h>
#include <ae2f/Cast.h>

typedef struct	UI		UI;
typedef struct	UIComBattleIdle	UIComBattleIdle;
typedef struct	Unit 		Unit;
typedef struct	Battle 		Battle;
typedef BATTLE_TEAMC_T		battle_teamc_t;
typedef BATTLE_FIGHTERC_T	battle_fighterc_t;


/** @brief 
 * as an input:	an order(cursor).	
 * When 0, suggest it as first move.
 * as an output:	the next order(cursor). When act_END, stop.
 * */
typedef CURSOR_BATTLE_OUT_T	cursor_battle_out_t;

#define act_FIRSTMOVE	0
#define act_END		-1

/**
 * @brief
 * The behaviour of one.
 * Meant to be iteratively called.
 * */
typedef err_t act_t(
		UI*,			/** @param UI */
		Battle*,		/** @param battlefield				*/
		UIComBattleIdle*
		);

/** @brief Actions Enum */
typedef enum eActs {
	/** @brief Null. */
	eActs_NIL,
	/** @brief It is a tutorial */
	eActs_TUTORIAL,
	eActs_IDLE,
	/** @brief Length of all Acts */
	eActs_LEN,
} eActs, eActs_t;

/** @brief List of Acts. To specify, see `eActs`. */
ae2f_extern ae2f_SHAREDCALL act_t* Acts[eActs_LEN];

/** @brief Invoke the function */
#define ActInvoke(a, battle, ui, uicom) \
	(((a)->act) % (size_t)eActs_LEN)[Acts](battle, ui, uicom)

typedef struct Act {
	ae2f_WhenC(enum) eActs act;
#if ae2f_WhenCXX(!)0
	inline err_t Invoke(
			UI*			ui,
			Battle* 		battle, 
			UIComBattleIdle*	p_uicomponent
			)
	{
		return ActInvoke(
				this
				, battle
				, ui
				, p_uicomponent
				);
	}


#endif
} Act;

#endif
