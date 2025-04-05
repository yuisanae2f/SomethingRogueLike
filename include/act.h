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
		Unit*,			/** @param the one casting this			*/	
		Battle*,		/** @param battlefield				*/
		battle_teamc_t, 	/** @param team index		(target)	*/
		battle_fighterc_t, 	/** @param fighter index	(target)	*/
		cursor_battle_out_t*,	/** @param 

					  as an input:	an order(cursor).	When 0, suggest it as first move.
					  as an output:	the next order(cursor). When act_END, stop.
					  */
		UIComBattleIdle*
		);

/** @brief Actions Enum */
enum eActs {
	eActs_ZERO,

	/** @brief Length of all Acts */
	eActs_LEN,
};

/** @brief List of Acts. To specify, see `eActs`. */
ae2f_extern ae2f_SHAREDCALL act_t* Acts[eActs_LEN];

/** @brief Invoke the function */
#define ActInvoke(a, unit, battle, teamc, fighterc, ui) \
	(((a)->act) % (size_t)eActs_LEN)[Acts](unit, battle, teamc, fighterc, ui)

typedef struct Act {
	ae2f_WhenC(enum) eActs act;
#if ae2f_WhenCXX(!)0
	inline err_t Invoke(
			UI*			ui,
			Unit*			unit, 
			Battle* 		battle, 
			battle_teamc_t		teamc, 
			battle_fighterc_t	fighterc,  
			cursor_battle_out_t*	p_cursor,
			UIComBattleIdle*	p_uicomponent
			)
	{
		return ActInvoke(
				ui
				, this
				, unit
				, battle
				, teamc
				, fighterc
				, p_cursor
				, p_uicomponent
				);
	}
#endif
} Act;

#endif
