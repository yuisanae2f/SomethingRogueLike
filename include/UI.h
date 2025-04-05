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
#include "./err.h"

/** @brief General IO */
typedef struct UI		UI;

/** @brief Selection Function IO */
typedef struct UISel		UISel;

/** @brief Output UI for which has Name, and Description. */
typedef struct UIND		UIND;

/** @brief 
 * UI for dialog.
 * Like stream, but less features.
 * */
typedef struct UILog		UILog;

/** @brief The components related to UI. */
typedef union UIComponent 	UIComponent;

/** 
 * @brief
 * UI for file (save, load).
 * Opening files when making a new object is the expected behaviour.
 * */
typedef struct UIFile		UIFile;

#define UIIsReady_YES	1
#define UIIsReady_NO	0

/** @todo Tell if UI ready to change. */
ae2f_extern ae2f_SHAREDCALL
bool UIIsReady(
		UI*
		);

/** @todo Make UI ready at all cost. */
ae2f_extern ae2f_SHAREDCALL
err_t UIForceReady(
		UI*
		);

/**
 * @todo
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
err_t UINDDel(
		UI*
		, UIND*
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
	eUIGestures g;	/** @brief gesture */
	int extra;	/** @brief extra */
}  UIGesture_t;

typedef struct Battle Battle;

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

	/** @brief SuperMenu */
	eUILocs_TITIL,
	eUILocs_TITIL_SAVE,
	eUILocs_TITIL_LOAD,

	eUILocs_LEN
} eUILocs;

/** @brief Make new UI. */
ae2f_extern ae2f_SHAREDCALL
UI* UIMk();

/**
 * @todo Change, or initiate the state.
 * */
ae2f_extern ae2f_SHAREDCALL
err_t UIInit(
		UI*

		/**
		 * @param game
		 * Give him nothing to NOT change game pointer. 
		 * */
		, Battle* 
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

/** @todo Kill UI. */
ae2f_extern ae2f_SHAREDCALL
err_t UIDel(UI*);

/** @todo Convert something to gesture */
ae2f_extern ae2f_SHAREDCALL
UIGesture_t UIGesture(
		UI* 
		);

/** @todo 
 * Check UI's current state (is it able to function)
 * */
ae2f_extern ae2f_SHAREDCALL
err_t UIVerify(UI*);

ae2f_extern ae2f_SHAREDCALL
err_t UILogPuts(
		UI*,
		UILog*,
		const char_t*
		);

/** @todo Clear the Log, like `cls` or `clear` on terminal output. */
ae2f_extern ae2f_SHAREDCALL
err_t UILogClear(
		UI*,
		UILog*
		);

/** @todo Kill the log, I mean, release the log. */
ae2f_extern ae2f_SHAREDCALL
err_t UILogDel(
		UI*,
		UILog*
		);

ae2f_extern ae2f_SHAREDCALL
err_t UIErrLogPuts(
		UI*,
		const char_t*
		);

/**
 * @todo
 * Load the selection.
 * */
ae2f_extern ae2f_SHAREDCALL
err_t	UISelLoad(UI*, UISel*, const str_t);

/**
 * @todo
 * Kill UISel made with `UISelBattleMk`
 *
 * */
ae2f_extern ae2f_SHAREDCALL
err_t	UISelDel(UI*, UISel*);

#include "./battle.h"

typedef unsigned char	UIFilec_t;
#define UIFile_MAX	3

/** @brief type of UIComponent::mBattleIdle */
typedef struct UIComBattleIdle	UIComBattleIdle;

union UIComponent {
	struct {
		UISel
			* Back, /** @brief 0 */ 
			* Save, /** @brief 1 */
			* Load, /** @brief 2 */
			* Quit; /** @brief 3 */
	} mTitil; /** @brief aka supermenu */

	struct {
		UIFile*	F[UIFile_MAX]; /** @brief 0 ~ 3 */
		UILog*	Log;
		UISel*	Titil;	/** @brief aka Menu, 3 */
	} mTitilSave, mTitilLoad;

	struct {
		UIND*	Units[UINDBattleSz];
		UISel
			* Skill,	/** @brief 0 */
			* Item,		/** @brief 1 */
			* Menu;		/** @brief 2 */
	} mBattle;

	struct ae2f_WhenCXX(::) UIComBattleIdle {

	} mBattleIdle;
};

/** @todo Save battles to files */
ae2f_extern ae2f_SHAREDCALL
err_t 	UIFilePuts(
		UI*
		, UIFile*
		, const Battle*
		);

/** @todo Load battles from files */
ae2f_extern ae2f_SHAREDCALL
err_t	UIFileGets(
		UI*
		, UIFile*
		, Battle*
		);

ae2f_extern ae2f_SHAREDCALL
err_t	UIFileLoad(
		UI*
		, UIFile*
		, const str_t
		);

ae2f_extern ae2f_SHAREDCALL
err_t	UIFileDel(
		UI*
		, UIFile*
		);

#endif
