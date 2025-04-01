#ifndef stat_h
#define stat_h

#include "./stat.auto.h"
#include "./skill.h"
#include "./inv.h"

/** @brief stat int type */
typedef STAT_INT_T stat_int_t;

/** 
 * @brief 
 * Fightable status type 
 * */
typedef struct Stat {
	stat_int_t
		hp, mp;

	/** skill **/
	SkillMenu skillmenu;
} Stat;

#endif
