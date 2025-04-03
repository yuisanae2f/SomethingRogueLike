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

#include "./str.h"

/**
 * Healthcheck. \n
 * 0 for healthy. \n
 * Positive for minour issues. \n
 * Negative for majour issues.
 * */
typedef int err_t;

/** @brief General IO */
typedef struct UI		UI;

/** @brief Selection Function IO */
typedef struct UISel		UISel;

/** @brief Output UI for which has Name, and Description. */
typedef struct UIND		UIND;

/** @brief The components related to UI. */
typedef union UIComponent 	UIComponent;

/**
 * @brief
 * Reload the UIND, as str_t and strlong_t
 *
 * Changes are not meant to be done for this function.
 * */
ae2f_extern ae2f_SHAREDCALL 
err_t UINDLoad(
		UI*
		, UIND*
		, const str_t
		, const strlong_t
		);

ae2f_extern ae2f_SHAREDCALL
err_t UIComponentLoad(
		UI*
		, UIComponent*
		);

/** @brief standard indexing for lpUIUnitBattle */
#define UINDBattleIdxer(fighteri, teami)	((teami) * BATTLE_FIGHTER_MAX + (fighteri))

/** @brief Count suggested for lpUIUnitBattle */ 
#define UINDBattleSz				(BATTLE_TEAM_MAX * BATTLE_FIGHTER_MAX)

/** @brief 
 * Gestures, input for something
 * */
typedef enum eUIGestures {
	/** @brief Nothing */
	eUIGestures_NONE,

	/** @brief 
	 * Escape
	 * */
	eUIGestures_ESC,

	/** @brief Cursor Move */
	eUIGestures_MOV,

	/** @brief 
	 * Hit, actual selection.
	 *
	 * UIGesture_t::extra would give you the cursor which is selected.
	 * Negative value of UIGesture_t::extra means you don't need to change the cursor. 
	 * */
	eUIGestures_HIT,

	/** @brief Toggle, Cursor Teleport */
	eUIGestures_TOGGLE,

	eUIGestures_SUPERMENU,

	eUIGestures_LEN
} eUIGestures;

typedef struct UIGesture_t {
	eUIGestures g;	/* gesture */
	int extra;	/* extra */
}  UIGesture_t;

typedef struct Game Game;

/**
 * @brief
 * UI: Current Location
 * */
typedef enum eUILocs {
	/** @brief Renew this shit. */
	eUILocs_NONE,

	eUILocs_TUTORIAL,

	eUILocs_BATTLE,
	eUILocs_BATTLE_INV,
	eUILocs_BATTLE_SKILLMENU,
	eUILocs_BATTLE_ITEM,
	eUILocs_BATTLE_SKILL,
	eUILocs_BATTLE_TARGET_TEAM,
	eUILocs_BATTLE_TARGET_MEMBER,
	eUILocs_BATTLE_TEAM,
	eUILocs_BATTLE_ANNOUNCING,
	/* TITIL */
	eUILocs_SUPERMENU,
	eUILocs_LEN
} eUILocs;

/** @brief Make new UI. */
ae2f_extern ae2f_SHAREDCALL
UI* UIMk();

/**
 * @brief Change, or initiate the state.
 * */
ae2f_extern ae2f_SHAREDCALL
err_t UIInit(
		UI*

		/**
		 * @param game
		 * Give him nothing to NOT change game pointer. 
		 * */
		, Game* 
		, eUILocs

		/**
		 * @param component
		 * Make new components and pass it via this pointer.
		 * When passed zero, do not make new component for them.
		 *
		 * Releasing them must be performed manually.
		 * */
		, UIComponent* 
		);

/* Reload */
#define UILoad(ui) UIInit(ui, 0, eUILocs_NONE, 0)

/** @brief return its parent, `Game`. */
ae2f_extern ae2f_SHAREDCALL
Game* UIGamePtr(UI*);

/** @brief Kill UI. */
ae2f_extern ae2f_SHAREDCALL
err_t UIDel(UI*);

/** @brief Convert something to gesture */
ae2f_extern ae2f_SHAREDCALL
UIGesture_t UIGesture(
		UI* 
		);

/** @brief 
 * Check UI's current state (is it able to function)
 * */
ae2f_extern ae2f_SHAREDCALL
err_t UIVerify(UI*);

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
UISel
*	UISelBattleMk(UI*)
,*	UISelSuperMenuMk(UI*);

/**
 * @brief
 * Load the selection.
 * */
ae2f_extern ae2f_SHAREDCALL
err_t	UISelLoad(UI*, UISel*, const str_t);

/**
 * @brief
 * Kill UISel made with `UISelBattleMk`
 *
 * */
ae2f_extern ae2f_SHAREDCALL
err_t	UISelDel(UI*, UISel*);

union UIComponent {
	struct {
		UISel
			* Back, 
			* Save, 
			* Load, 
			* Quit;
	} mSuperMenu;
};

#endif
