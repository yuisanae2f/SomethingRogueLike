#include <game.h>
#include <UI.h>
#include <assert.h>

int main() { return 0; }

#define game (*p_game)

err_t GameMain(Game* p_game) {
	/** @brief 
	 * Contains number in state of error. 
	 * 0 for okay.
	 * */
	err_t e;

	/**
	 * This section is Pathfinder.
	 * Here, it will check `dest` for destination.
	 * */
PATHFINDER:
	/* Global initiation sector */
	assert(game.locdest != eUILocs_LEN);
	assert(UIVerify(game.ui) >= 0);

	if(!game.hastutorialpassed)
		goto MAINSTART;

	e = UIInit(game.ui, 0, game.locdest, &game.com);
	assert(e >= 0);

	switch(game.locdest) {
		case eUILocs_LEN:
			return -1;
		case eUILocs_TITIL:
			goto TITILSTART;

		case eUILocs_TITIL_LOAD:
		case eUILocs_TITIL_SAVE:
			goto TITIL_SAVELOADSTART;

		case eUILocs_BATTLE:
			goto BATTLESTART;

		case eUILocs_BATTLE_TEAM:
			goto TEAMSTART;
	}

	return -1; /* Finding path has failed. */

	/**
	 * aka
	 * - Super Menu 
	 * - Main Menu
	 * */

MAINSTART:
	game = ae2f_RecordMk(Game, 0, );
	game.loclast = eUILocs_TUTORIAL;
	game.ui = UIMk();

	assert(UIVerify(game.ui) >= 0); /* When failed. */
	/* init */
	UIInit(game.ui, &game.battle, eUILocs_NONE, 0);
	goto PATHFINDER;
MAINEND: /* Programme is ending. */
	return UIDel(game.ui);

TITILSTART:
	game.cursor.smenu = eSuperMenu_BACK;

	assert(game.loclast != eUILocs_TITIL);
	assert(game.com.mTitil.Back);
	assert(game.com.mTitil.Save);
	assert(game.com.mTitil.Load);
	assert(game.com.mTitil.Quit);

	e  = UISelLoad(
			game.ui
			, game.com.mTitil.Back
			, game.hastutorialpassed 
			? "Back to game" : "New Game"
			);
	e |= UISelLoad(
			game.ui
			, game.com.mTitil.Load
			, "Load"
			);
	e |= UISelLoad(
			game.ui
			, game.com.mTitil.Save
			, "Save"
			);
	e |= UISelLoad(
			game.ui
			, game.com.mTitil.Quit
			, "Quit"
			);
	assert(e >= 0);

TITILLOOP:
	game.gest = UIGesture(game.ui);
	switch(game.gest.g) {
		case eUIGestures_LEN: 
			assert(0);

		case eUIGestures_SUPERMENU:
			if(game.hastutorialpassed) {
				game.cursor.smenu = eSuperMenu_BACK;
				goto TITILLOOP_eUIGestures_HIT;
			}
			break;
		case eUIGestures_ESC:
TITILLOOP_eUIGestures_ESC:
			game.cursor.smenu = eSuperMenu_QUIT;
		case eUIGestures_HIT:
TITILLOOP_eUIGestures_HIT:
			e  = UISelDel(game.ui, game.com.mTitil.Save);
			e |= UISelDel(game.ui, game.com.mTitil.Back);
			e |= UISelDel(game.ui, game.com.mTitil.Save);
			e |= UISelDel(game.ui, game.com.mTitil.Load);
			assert(e >= 0);

			switch(game.cursor.smenu) {
				case eSuperMenu_BACK:
					game.locdest = game.loclast;
					goto PATHFINDER;
				case eSuperMenu_LOAD:
					game.locdest = eUILocs_TITIL_LOAD;
					goto PATHFINDER;
				case eSuperMenu_QUIT:
					goto TITILLOOP_eUIGestures_ESC;
				case eSuperMenu_SAVE:
					game.locdest = eUILocs_TITIL_SAVE;
					goto MAINEND;
				case eSuperMenu_LEN: 
					assert(0);
			} assert(0);
		case eUIGestures_MOV:
			game.gest.extra += game.cursor.smenu;
		case eUIGestures_TOGGLE:
			assert(game.gest.extra >= 0);
			game.cursor.smenu = game.gest.extra % eSuperMenu_LEN;
		case eUIGestures_NONE:
			break;
	}

	e = UILoad(game.ui);
	assert(e >= 0);
	goto TITILLOOP;

TITIL_SAVELOADSTART:
	game.cursor.saveload = 0;

	assert(UIVerify(game.ui) >= 0);
	assert(game.com.mTitilSave.Log);
	assert(game.com.mTitilSave.F[0]);
	assert(game.com.mTitilSave.F[1]);
	assert(game.com.mTitilSave.F[2]);

	e =	UILogPuts(
			game.ui
			, game.com.mTitilSave.Log
			, game.locdest == eUILocs_TITIL_LOAD 
			? "Select your file to load."

			: game.hastutorialpassed 
			? "Select your file to save." 
			: "Select your file to erase."
			);

	e |=	UIFileLoad(game.ui, game.com.mTitilSave.F[0], "File 1");
	e |=	UIFileLoad(game.ui, game.com.mTitilSave.F[1], "File 2");
	e |=	UIFileLoad(game.ui, game.com.mTitilSave.F[2], "File 3");
	e |=	UISelLoad(game.ui, game.com.mTitilSave.Titil, "Go Back");
	assert(e >= 0);

	/* 
	 * Fun fact:
	 * Saving screen and loading screen's UI are quite similar.
	 * */
TITIL_SAVELOADLOOP:
	game.gest = UIGesture(game.ui);
	switch(game.gest.g) {
		case eUIGestures_LEN:
			assert(0);


		case eUIGestures_ESC:
		case eUIGestures_SUPERMENU:
			game.cursor.saveload = 3; /* Go back */
		case eUIGestures_HIT:
			switch(game.cursor.saveload) {
				case 0:
				case 1:
				case 2:
					if(game.locdest == eUILocs_TITIL_SAVE) 
					{
						e = UIFilePuts(
								game.ui
								, game.com.mTitilSave.F[game.cursor.saveload]
								, &game.battle
								);
						assert(e >= 0);
						break;
					} else {
						e = UIFileGets(
								game.ui
								, game.com.mTitilLoad.F[game.cursor.saveload]
								, &game.battle
								);
						assert(e >= 0);
						game.locdest = eUILocs_BATTLE;
						goto TITIL_SAVELOADEND;
					}
				case 3:
					game.locdest = eUILocs_TITIL;
					goto TITIL_SAVELOADEND;
				default: assert(0);
			}

		case eUIGestures_MOV:
			game.gest.extra += game.cursor.saveload;
		case eUIGestures_TOGGLE:
			assert(game.gest.extra >= 0);
			game.cursor.smenu = game.gest.extra & 3; /* 
						`		      I have four menu here.
								      This would be enough since what I need is (N MOD 4).
								      */
		case eUIGestures_NONE:
			break;
	}

	UILoad(game.ui);
	goto TITIL_SAVELOADLOOP;

TITIL_SAVELOADEND:
	e =	UIVerify(game.ui);
	e |= 	UISelDel(game.ui, game.com.mTitilSave.Titil);
	e |=	UILogDel(game.ui, game.com.mTitilSave.Log);
	e |=	UIFileDel(game.ui, game.com.mTitilSave.F[0]);
	e |=	UIFileDel(game.ui, game.com.mTitilSave.F[1]);
	e |=	UIFileDel(game.ui, game.com.mTitilSave.F[2]);
	assert(e >= 0); goto PATHFINDER;

BATTLESTART:
	e = 0;
	e |= UIVerify(game.ui);

	game.cursor.battle = 0;
	for(battle_teamc_t ti = 0; ti < game.battle.c; ti++)
		for(battle_fighterc_t fi = 0; fi < game.battle.v[ti].c; fi++)
			e |=	UINDLoad(
					game.ui
					, game.com.mBattle.Units[UINDBattleIdxer(fi, ti)]
					, game.battle.v[ti].v[fi].name
					, game.battle.v[ti].v[fi].desc
					);	

	e |= UISelLoad(game.ui, game.com.mBattle.Item, "Item");
	e |= UISelLoad(game.ui, game.com.mBattle.Menu, "Menu");
	e |= UISelLoad(game.ui, game.com.mBattle.Skill, "Skill");
	assert(e >= 0);
BATTLELOOP:
	assert(UIVerify(game.ui) >= 0);
	game.gest = UIGesture(game.ui);

	if(game.turnID)
		goto BATTLELOOP_TURN_OTHERS;


BATTLELOOP_TURN_YOURS:
	switch(game.gest.g) {
		case eUIGestures_LEN: 
			assert(0);

		case eUIGestures_MOV:
			game.gest.extra += game.cursor.battle;
		case eUIGestures_TOGGLE:
			game.cursor.battle = game.gest.extra % game.battle.c + 2;
			break;

		/* Supermenu pop up */
		case eUIGestures_ESC:
		case eUIGestures_SUPERMENU:
			game.cursor.battle = game.battle.c + 1; /* index, last, which will let you to TITIL. */

		case eUIGestures_HIT:
			/* Team indexer. For one team. */
			if(game.cursor.battle < game.battle.c) {
				game.fighter = game.cursor.battle;
				game.locdest = eUILocs_BATTLE_TEAM;
			} else {
				switch(game.cursor.battle - game.battle.c)
				{
					case 0: /* Inventory */
						game.locdest = eUILocs_BATTLE_INV;
						break;
					case 1: /* TITIL */
						game.locdest = eUILocs_TITIL;
						break;
					default:
						assert(0); /* I don't know you */
				}
			}

			goto BATTLEEND;
		case eUIGestures_NONE:
			break;	
	}

	goto BATTLELOOP_LOAD;

	/* 
	 * It is not your turn.
	 *
	 * This will basically work as an output for your input,
	 * which stands for "your turn".
	 * */
BATTLELOOP_TURN_OTHERS:
	switch(game.gest.g) {
BATTLELOOP_TURN_OTHERS_IDLE:
		default:
			break;
		case eUIGestures_HIT:
			if(!UIIsReady(game.ui)) {
				e = UIForceReady(game.ui);
				assert(e >= 0);
				goto BATTLELOOP_TURN_OTHERS_IDLE;
			}
			break;
	}
	goto BATTLELOOP_LOAD;

	/* Or so it is called rendering. */
BATTLELOOP_LOAD:

	/* Reloading the components. */
	e = 0;
	for(battle_teamc_t ti = 0; ti < game.battle.c; ti++)
		for(battle_fighterc_t fi = 0; fi < game.battle.v[ti].c; fi++)
			e |=	UINDLoad(game.ui, game.com.mBattle.Units[UINDBattleIdxer(fi, ti)], 0, 0);
	
	e |= UISelLoad(game.ui, game.com.mBattle.Item, 	0);
	e |= UISelLoad(game.ui, game.com.mBattle.Menu, 	0);
	e |= UISelLoad(game.ui, game.com.mBattle.Skill,	0);

	assert(e >= 0);
	UILoad(game.ui);

	goto BATTLELOOP;
	
BATTLEEND:
	
	e = 0;
	for(battle_teamc_t ti = 0; ti < game.battle.c; ti++)
		for(battle_fighterc_t fi = 0; fi < game.battle.v[ti].c; fi++)
			e |= UINDDel(game.ui, game.com.mBattle.Units[UINDBattleIdxer(fi, ti)]);

	e |= UISelDel(game.ui, game.com.mBattle.Item);
	e |= UISelDel(game.ui, game.com.mBattle.Menu);
	e |= UISelDel(game.ui, game.com.mBattle.Skill);

	assert(e >= 0);
	goto PATHFINDER;

TEAMSTART:
TEAMLOOP:
TEAMEND:
	assert(0);
}
