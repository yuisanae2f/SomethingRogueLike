#include <game.h>
#include <UI.h>
#include <assert.h>

err_t main() {
MAINSTART:;
	Game game = {0, };
	game.supermenu.last = eUILocs_TUTORIAL;
	game.ui = UIMk();
	assert(UIVerify(game.ui) >= 0); /* When failed. */
	UIGesture_t gesture;
	UIComponent component = {0, };
	err_t e;

	goto SUPERMENUSTART;

MAINEND: /* Programme is ending. */
	return UIDel(game.ui);

	/**
	 * This section is Pathfinder.
	 * Here, it will check game.supermenu.last for destination.
	 * */
PATHFINDER:
	assert(game.supermenu.last != eUILocs_LEN);
	switch(game.supermenu.last) {
		case eUILocs_LEN:
			return -1;

		case eUILocs_SUPERMENU:
			goto SUPERMENUSTART;
	}

	return -1; /* Finding path has failed. */

SUPERMENUSTART:
	game.supermenu.cursor = eSuperMenu_BACK;
	assert(game.supermenu.last != eUILocs_SUPERMENU);
	assert(UIVerify(game.ui) >= 0);

	e = UIInit(
			game.ui
			, &game
			, eUILocs_SUPERMENU
			, &component
			); 
	assert(e);

	assert(component.mSuperMenu.Back);
	assert(component.mSuperMenu.Save);
	assert(component.mSuperMenu.Load);
	assert(component.mSuperMenu.Quit);

	e  = UISelLoad(
			game.ui
			, component.mSuperMenu.Back
			, game.hastutorialpassed 
			? "Back to game" : "New Game"
			);
	e |= UISelLoad(
			game.ui
			, component.mSuperMenu.Load
			, "Load"
			);
	e |= UISelLoad(
			game.ui
			, component.mSuperMenu.Save
			, "Save"
			);
	e |= UISelLoad(
			game.ui
			, component.mSuperMenu.Quit
			, "Quit"
			);
	assert(e >= 0);

SUPERMENULOOP:
	gesture = UIGesture(game.ui);
	switch(gesture.g) {
		case eUIGestures_LEN: 
			assert(0);

		case eUIGestures_SUPERMENU:
			if(game.hastutorialpassed) {
				game.supermenu.cursor = eSuperMenu_BACK;
				goto _eUIGestures_HIT;
			}
			break;
		case eUIGestures_ESC:
			game.supermenu.cursor = eSuperMenu_QUIT;
		case eUIGestures_HIT:
_eUIGestures_HIT:
			e  = UISelDel(game.ui, component.mSuperMenu.Save);
			e |= UISelDel(game.ui, component.mSuperMenu.Back);
			e |= UISelDel(game.ui, component.mSuperMenu.Save);
			e |= UISelDel(game.ui, component.mSuperMenu.Load);
			assert(e >= 0);

			switch(game.supermenu.cursor) {
				case eSuperMenu_BACK:
				case eSuperMenu_LOAD:
				case eSuperMenu_QUIT:
					goto MAINEND;
				case eSuperMenu_SAVE:
				case eSuperMenu_LEN: assert(0);
			} assert(0);
		case eUIGestures_MOV:
			gesture.extra += game.supermenu.cursor;
		case eUIGestures_TOGGLE:
			assert(gesture.extra >= 0);
			game.supermenu.cursor = gesture.extra % eSuperMenu_LEN;
		case eUIGestures_NONE:
			break;
	}

	e = UILoad(game.ui);
	assert(e >= 0);
	goto SUPERMENULOOP;
}
