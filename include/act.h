#ifndef act_h
#define act_h

#include "./battle.auto.h"
#include "./err.h"
#include <ae2f/Call.h>
#include <ae2f/Cast.h>

typedef struct	UI		UI;

typedef struct	Unit 		Unit;
typedef struct	Battle 		Battle;
typedef BATTLE_TEAMC_T		battle_teamc_t;
typedef BATTLE_FIGHTERC_T	battle_fighterc_t;

/**
 * The behaviour
 * */
typedef err_t act_t(
		Unit*,			// the one casting this
		Battle*,		// battlefield
		battle_teamc_t, 	// team index
		battle_fighterc_t, 	// fighter index (target)
		UI*			// ui api
		);

typedef err_t actidle_t(
		
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
			Unit* unit, 
			Battle* battle, 
			battle_teamc_t teamc, 
			battle_fighterc_t fighterc,  
			UI* ui 
			)
	{
		return ActInvoke(
				this
				, unit
				, battle
				, teamc
				, fighterc
				, ui
				);
	}
#endif
} Act;

#endif
