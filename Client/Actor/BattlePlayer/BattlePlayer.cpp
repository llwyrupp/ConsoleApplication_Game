#include "BattlePlayer.h"
#include "Game/Game.h"
#include "InputMgr/InputMgr.h"
#include "Level/BattleLevel/BattleLevel.h"
#include "EngineCommon/Engine_Function.h"

using namespace System;

BattlePlayer::BattlePlayer()
	:super("", "", Vector2::Zero, Color::eGreen)
{
	//read player stat from file.
	LoadPlayerStat("../Data/Player/PlayerStat.txt");
}

BattlePlayer::~BattlePlayer()
{
	SavePlayerStat("../Data/Player/PlayerStat.txt");
}

void BattlePlayer::BeginPlay()
{
}

void BattlePlayer::Tick(float _fDeltaTime)
{
#pragma region BATTLELEVEL

	Game* pInstance = &(Game::Get_Instance());
	CheckIfNullReturn(pInstance);
	BattleLevel* pBattleLevel = dynamic_cast<BattleLevel*>(pInstance->Get_MainLevel());
	CheckIfNullReturn(pBattleLevel);

	if (pInstance->GetCurLevelType() == E_LEVEL_TYPE::E_LEVELTYPE_BATTLE &&
		pBattleLevel->GetBattleSequence() == E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT) {
		if (InputMgr::Get_Instance().GetKey('A')) {//fight.
			pBattleLevel->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
			pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_ATTACK);
		}
		if (InputMgr::Get_Instance().GetKey('G')) {//guard
			pBattleLevel->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
			pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_GUARD);
		}
		if (InputMgr::Get_Instance().GetKey('I')) {//item.
			pBattleLevel->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
			pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_ITEM);
		}
		if (InputMgr::Get_Instance().GetKey('R')) {//run.
			pBattleLevel->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
			pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_RUN);
		}

		//Select Item
		if (pBattleLevel->GetPlayerAction() == E_PLAYERACTION::E_PLAYERACTION_ITEM) {
			/*if (InputMgr::Get_Instance().GetKeyDown(VK_LEFT)) {

			}
			if (InputMgr::Get_Instance().GetKeyDown(VK_RIGHT)) {

			}*/
			if (InputMgr::Get_Instance().GetKeyDown(VK_UP)) {//change idx(upwards)
				int iNextIdx = pBattleLevel->GetCurInvenIdx() - 1;
				iNextIdx = iNextIdx < 0 ? MAX_PLAYERINVEN_SIZE - 1 : iNextIdx;
				pBattleLevel->SetCurInvenIdx(iNextIdx);
			}
			if (InputMgr::Get_Instance().GetKeyDown(VK_DOWN)) {//change idx(downwards)
				int iNextIdx = pBattleLevel->GetCurInvenIdx() + 1;
				iNextIdx = iNextIdx >= MAX_PLAYERINVEN_SIZE ? 0 : iNextIdx;
				pBattleLevel->SetCurInvenIdx(iNextIdx);
			}
			if (InputMgr::Get_Instance().GetKeyDown(VK_SPACE)) {//decide
				pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_USEITEM);
			}
		}
	}
#pragma endregion BATTLELEVEL
}

void BattlePlayer::Render()
{
}


void BattlePlayer::LoadPlayerStat(const char* _pPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, _pPath, "rt");

	if (!pFile)
	{
		cerr << "FAILED TO LOAD PLAYERSTAT.txt";
		__debugbreak();
	}

	char cBuffer[MAX_BUFFER_LEN] = {};
	char* pToken = {};
	char* pContext = {};
	size_t szLen = fread(cBuffer, sizeof(char), MAX_BUFFER_LEN, pFile);
	if (szLen == 0) {
		cerr << "No file at: " << _pPath;
		__debugbreak();
	}

	pToken = strtok_s(cBuffer, "\n", &pContext);

	while (pToken) {
		char pHeader[MAX_HEADER_LEN] = {};
		sscanf_s(pToken, "%s", pHeader, MAX_HEADER_LEN);

		if (!strcmp(pHeader, "iHP")) {
			sscanf_s(pToken, "iHP = %d", &m_tInfo.iHP);
		}
		else if (!strcmp(pHeader, "iMP")) {
			sscanf_s(pToken, "iMP = %d", &m_tInfo.iMP);
		}
		else if (!strcmp(pHeader, "iAttack")) {
			sscanf_s(pToken, "iAttack = %d", &m_tInfo.iAttack);
		}
		else if (!strcmp(pHeader, "iDefense")) {
			sscanf_s(pToken, "iDefense = %d", &m_tInfo.iDefense);
		}
		else if (!strcmp(pHeader, "iCritRate")) {
			sscanf_s(pToken, "iCritRate = %d", &m_tInfo.iCritRate);
		}
		else if (!strcmp(pHeader, "iCritDmg")) {
			sscanf_s(pToken, "iCritDmg = %d", &m_tInfo.iCritDmg);
		}

		pToken = strtok_s(nullptr, "\n", &pContext);
	}


	fclose(pFile);
}

void BattlePlayer::SavePlayerStat(const char* _pPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, _pPath, "wt");

	if (!pFile)
	{
		cerr << "FAILED TO LOAD PLAYERSTAT.txt";
		__debugbreak();
	}


	fprintf(pFile, "iHP = %d\n", m_tInfo.iHP);
	fprintf(pFile, "iMP = %d\n", m_tInfo.iMP);
	fprintf(pFile, "iAttack = %d\n", m_tInfo.iAttack);
	fprintf(pFile, "iDefense = %d\n", m_tInfo.iDefense);
	fprintf(pFile, "iCritRate = %d\n", m_tInfo.iCritRate);
	fprintf(pFile, "iCritDmg = %d\n", m_tInfo.iCritDmg);

	fclose(pFile);
}
