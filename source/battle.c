#include <battle.h>
#include <stdlib.h>

lpUIUnitBattle UIUnitBattleMk(UI*, Battle*);
err_t UIUnitBattleDel(UI*, lpUIUnitBattle);
err_t UIUnitDel(UI*, UIUnit*);

ae2f_extern ae2f_SHAREDCALL
err_t BattleInvInit(Inv*, UI*);
ae2f_extern ae2f_SHAREDCALL
err_t BattleInvLoad(Inv*, UI*);
ae2f_extern ae2f_SHAREDCALL
err_t BattleInvDel(Inv*, UI*);

ae2f_extern ae2f_SHAREDCALL
err_t BattleTeamInit(Battle_Team*, UI*);
ae2f_extern ae2f_SHAREDCALL
err_t BattleTeamLoad(Battle_Team*, UI*);
ae2f_extern ae2f_SHAREDCALL
err_t BattleTeamDel(Battle_Team*, UI*);

ae2f_SHAREDEXPORT
err_t BattleInit(
		Battle* battle,
		UI* ui
		)
{
	err_t err = UIVerify(ui);
	if(err < 0) return err;

	if(!battle) {

		UIErrLogPuts(ui, "BattleInit[Fatal]: UI is null. ");
		return -1;
	}

	err = UIInit(ui, 0, eUILocs_BATTLE);
	if(err < 0) {
		UIErrLogPuts(ui, "BattleInit[Fatal]: UIInit has failed.");
		return err;
	}

	if(!battle->uisel) battle->uisel = UISelBattleMk(ui);
	if(!battle->uisel) {
		UIErrLogPuts(ui, "BattleInit[Fatal]: UISelBattleMk has failed.");
		return -2;
	}

	battle->uicursor = 0;
	if(battle->c > BATTLE_TEAM_MAX) {
		UIErrLogPuts(ui, "BattleInit[Fatal]: battle->c is greater than BATTLE_TEAM_MAX");
	}

	if(!battle->uiunit) battle->uiunit = UIUnitBattleMk(ui, battle);
	if(!battle->uiunit) {
		UIErrLogPuts(ui, "BattleInit[Fatal]: UIUnitBattleMk has failed.");
	}

	return err;
}

ae2f_SHAREDEXPORT
err_t BattleDel(
		Battle* battle,
		UI* ui
		)
{
	err_t err = UIVerify(ui);
	if(err < 0) return -1;

	if(!battle) {
		UIErrLogPuts(ui, "BattleDel[Warning]: battle is null.");
		return 1; 
	}

	err = UISelBattleDel(ui, battle->uisel);
	if(err < 0) {
		UIErrLogPuts(ui, "BattleDel[Fatal]: UISelBattleDel has failed.");
		return -2; 
	}

	err = UIUnitBattleDel(ui, battle->uiunit);
	if(err < 0) {
		UIErrLogPuts(ui, "BattleDel[Fatal]: UIUnitBattleDel has failed.");
		return -3;
	}

	return err;
}

#include "./supermenu.h"

ae2f_SHAREDEXPORT
err_t BattleLoad(
		Battle* battle,
		const UIGestureRet* gesture,
		UI* ui
		)
{
	err_t err = UIVerify(ui);
	if(err < 0) return -1;

	if(!battle) {
		UIErrLogPuts(ui, "BattleLoad[Fatal]: battle is null");
		return -2; 
	}

	switch(gesture->g)
	{
		case eUIGestures_MOV:
			battle->uicursor = !battle->uicursor;
		case eUIGestures_NONE:
			return UILoad(ui);

		case eUIGestures_SEL:
			return battle->uicursor 
				? BattleTeamInit(
						battle->v + UIGamePtr(ui)->whoareyou
						, ui
						)

				: BattleInvInit(
						&battle->v[UIGamePtr(ui)->whoareyou].inv
						, ui
						);

		case eUIGestures_ESC:
		case eUIGestures_SUPERMENU:
			return SuperMenuInit(ui);

		case eUIGestures_LEN:
			UIErrLogPuts(ui, "gesture->g went something not expected.");
			return -3;
	}

	return UILoad(ui);
}
