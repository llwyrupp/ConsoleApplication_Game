#include "BattlePlayer.h"
#include "Game/Game.h"
#include "InputMgr/InputMgr.h"
#include "Level/BattleLevel/BattleLevel.h"


BattlePlayer::BattlePlayer()
	:super("", "", Vector2::Zero, Color::eGreen)
{
}

BattlePlayer::~BattlePlayer()
{
}

void BattlePlayer::BeginPlay()
{
}

void BattlePlayer::Tick(float _fDeltaTime)
{
#pragma region BATTLELEVEL
	if (Game::Get_Instance().GetCurLevelType() == E_LEVEL_TYPE::E_LEVELTYPE_BATTLE) {
		if (InputMgr::Get_Instance().GetKey('F')) {//fight.
			dynamic_cast<BattleLevel*>(Game::Get_Instance().Get_MainLevel())
				->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
		}
		if (InputMgr::Get_Instance().GetKey('G')) {//guard
			//dynamic_cast<BattleLevel*>(Game::Get_Instance().Get_MainLevel())->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
		}
		if (InputMgr::Get_Instance().GetKey('I')) {//item.

		}
		if (InputMgr::Get_Instance().GetKey('R')) {//run.
			//dynamic_cast<BattleLevel*>(Game::Get_Instance().Get_MainLevel())->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
		}
	}
#pragma endregion BATTLELEVEL
}

void BattlePlayer::Render()
{
}

