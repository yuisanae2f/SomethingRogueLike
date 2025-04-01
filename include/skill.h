#ifndef skill_h
#define skill_h

#include "./skill.auto.h"
#include "./act.h"

#include "./ArrLike.h"

/** skills */
typedef Act skillmenu_t[SKILL_MAX];
typedef SKILLC_T skillc_t;

typedef struct SkillMenu {
	skillmenu_t	v;
	skillc_t	c;

	ArrLikeInjection(, Act, skillc_t);
} SkillMenu;

#endif
