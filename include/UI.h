/**
 * @file UI.h
 *
 * @brief
 * This is up to you to implement. 
 * There are just bunch of UIs, NOT GAME ITSELF.
 * */
#ifndef UI_h
#define UI_h

#include <ae2f/Cast.h>
#include <ae2f/Call.h>

/**
 * Healthcheck. \n
 * 0 for healthy. \n
 * Positive for minour issues. \n
 * Negative for majour issues.
 * */
typedef int err_t;

/** @brief General IO */
typedef struct UI	UI;

/** @brief Selection Function IO */
typedef struct UISel	UISel;


typedef struct UIUnit	
/** 
 * * @brief IO for Showing Unit 
 * * */
UIUnit

/** 
 * @brief 
 * Vector as UIUnit on context of Battle. 
 * This is meant to be a pointer.
 * */
, *lpUIUnitBattle;


#include "./unit.h"
#include "./game.h"

/** @brief standard indexing for lpUIUnitBattle */
#define UIUnitBattleIdxer(fighteri, teami)	((teami) * BATTLE_FIGHTER_MAX + (fighteri))

/** @brief Count suggested for lpUIUnitBattle */ 
#define UIUnitBattleSz				(BATTLE_TEAM_MAX * BATTLE_FIGHTER_MAX)

/** @brief 
 * Parameter for `UIMk`
 *
 * Must not be 'alive' as class.
 * */
typedef struct UIMkPrm		UIMkPrm;

/** @brief 
 * Gestures, input for something
 * */
typedef enum eUIGestures {
	/** @brief Nothing */
	eUIGestures_NONE,

	/** @brief Escape */
	eUIGestures_ESC,

	/** @brief Cursor Move */
	eUIGestures_MOV,

	/** @brief Select */
	eUIGestures_SEL,

	eUIGestures_SUPERMENU,

	eUIGestures_LEN
} eUIGestures;

/**
 * @brief
 * UI: Current Location
 * */
typedef enum eUILocs {
	/** @brief Renew this shit. */
	eUILocs_NONE,
	eUILocs_BATTLE,
	
	eUILocs_BATTLE_INV,
	eUILocs_BATTLE_SKILLMENU,
	eUILocs_BATTLE_ITEM,
	eUILocs_BATTLE_SKILL,
	eUILocs_BATTLE_TARGET_TEAM,
	eUILocs_BATTLE_TARGET_MEMBER,
	eUILocs_BATTLE_TEAM,
	eUILocs_BATTLE_ANNOUNCING,
	eUILocs_SUPERMENU,

	/** @brief title */
	eUILocs_TITIL,
	eUILocs_LEN
} eUILocs;

/** @brief Make new UI. */
ae2f_extern ae2f_SHAREDCALL
UI* UIMk(const UIMkPrm*);

/**
 * @brief Change, or initiate the state.
 * */
ae2f_extern ae2f_SHAREDCALL
err_t UIInit(
		UI*
		,Game* /* Give him nothing to NOT change game pointer. */
		,eUILocs
		);

/* Reload */
#define UILoad(ui) UIInit(ui, 0, eUILocs_NONE)

/** @brief return its parent, `Game`. */
ae2f_extern ae2f_SHAREDCALL
Game* UIGamePtr(UI*);

/** @brief Kill UI. */
ae2f_extern ae2f_SHAREDCALL
err_t UIDel(UI*);

/** @brief Cursor, where you are pointing. */
typedef unsigned int cursor_t;
typedef struct UIGesturePrm	UIGesturePrm;
typedef struct UIGestureRet {
	eUIGestures g;	/* gesture */
	int extra;	/* extra */
} UIGestureRet;

/** @brief Convert something to gesture */
ae2f_extern ae2f_SHAREDCALL
err_t UIGesture(
		UIGestureRet*, 
		UIGesturePrm /* you decide what to get as input */
		);

/** @brief 
 * Check UI's current state (is it able to function)
 * */
ae2f_extern ae2f_SHAREDCALL
err_t UIVerify(UI*);

#include "./str.h"

ae2f_extern ae2f_SHAREDCALL
err_t UILogPuts(
		UI*,
		const char_t*
		);

ae2f_extern ae2f_SHAREDCALL
err_t UIErrLogPuts(
		UI*,
		const char_t*
		);

ae2f_extern ae2f_SHAREDCALL
err_t UILogClear(
		UI*
		);

/**
 * @brief
 * Get selections.
 * Two of them will be ready, non-initiating needed.
 * */
ae2f_extern ae2f_SHAREDCALL
UISel*	UISelBattleMk(UI*);

/**
 * @brief
 * Kill UISel made with `UISelBattleMk`
 *
 * */
ae2f_extern ae2f_SHAREDCALL
err_t	UISelBattleDel(UI*, UISel*);


#endif
