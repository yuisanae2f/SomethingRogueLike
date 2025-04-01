#ifndef supermenu_h
#define supermenu_h

#include "./UI.h"

/** @brief The menu which could pop up whenever. */
typedef struct SuperMenu {
	unsigned char cursor;
} SuperMenu;

ae2f_extern ae2f_SHAREDCALL
err_t SuperMenuInit(
		UI*
		);

ae2f_extern ae2f_SHAREDCALL
err_t SuperMenuLoad(
		SuperMenu*,
		const UIGestureRet*,
		UI*
		);

ae2f_extern ae2f_SHAREDCALL
err_t SuperMenuDel(
		SuperMenu*,
		UI*
		);

#endif
