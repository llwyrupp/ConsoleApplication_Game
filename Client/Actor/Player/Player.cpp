#include "Actor/Player/Player.h"
#include "InputMgr/InputMgr.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include "Game/Game.h"
#include "Level/BattleLevel/BattleLevel.h"
#include "EngineCommon/Engine_Function.h"

using namespace System;

Player::Player(const Vector2& vPos)
	:super(nullptr, "../Data/Player/Player.txt", vPos, Color::eGreen), m_fSpeed(20.f), m_fAccX(0.f), m_fAccY(0.f)
{
	m_iSortingOrder = 5;
	//LoadPlayerStat("../Data/Player/PlayerStat.txt");
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	super::BeginPlay();
}

void Player::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);


	//Input
	//FieldLevel Movement
#pragma region FIELDLEVEL
	static ICanPlayerMove* canPlayerMove = nullptr;

	if (!canPlayerMove && GetLevel()) {
		canPlayerMove = dynamic_cast<ICanPlayerMove*>(GetLevel());
	}

	Vector2 vNewPos = GetPos();

	if (Game::Get_Instance().GetCurLevelType() == E_LEVEL_TYPE::E_LEVELTYPE_FIELD) {

		if (InputMgr::Get_Instance().GetKey(VK_LEFT)) {
			--vNewPos.m_iX;
			if (canPlayerMove->CanMove(GetPos(), vNewPos)) {
				m_fAccX += _fDeltaTime * m_fSpeed;
				if (m_fAccX > 1.f) {
					m_fAccX = 0.f;
					SetPos(vNewPos);
				}
			}
		}
		if (InputMgr::Get_Instance().GetKey(VK_RIGHT)) {
			++vNewPos.m_iX;

			if (canPlayerMove->CanMove(GetPos(), vNewPos)) {
				m_fAccX += _fDeltaTime * m_fSpeed;
				if (m_fAccX > 1.f) {
					m_fAccX = 0.f;
					SetPos(vNewPos);
				}
			}
		}
		if (InputMgr::Get_Instance().GetKey(VK_UP)) {
			--vNewPos.m_iY;

			if (canPlayerMove->CanMove(GetPos(), vNewPos)) {
				m_fAccY += _fDeltaTime * m_fSpeed;
				if (m_fAccY > 1.f) {
					m_fAccY = 0.f;
					SetPos(vNewPos);
				}
			}
		}
		if (InputMgr::Get_Instance().GetKey(VK_DOWN)) {
			++vNewPos.m_iY;

			if (canPlayerMove->CanMove(GetPos(), vNewPos)) {
				m_fAccY += _fDeltaTime * m_fSpeed;
				if (m_fAccY > 1.f) {
					m_fAccY = 0.f;
					SetPos(vNewPos);
				}
			}
		}
	}
#pragma endregion FIELDLEVEL

#pragma region BATTLELEVEL
	else if (Game::Get_Instance().GetCurLevelType() == E_LEVEL_TYPE::E_LEVELTYPE_FIELD) {

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
				pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_SELECTITEM);
			}
			if (InputMgr::Get_Instance().GetKey('R')) {//run.
				pBattleLevel->SetBattleSequence(E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION);
				pBattleLevel->SetPlayerAction(E_PLAYERACTION::E_PLAYERACTION_RUN);
			}

			//Select Item
			if (pBattleLevel->GetPlayerAction() == E_PLAYERACTION::E_PLAYERACTION_SELECTITEM) {
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
	}
#pragma endregion BATTLELEVEL
}

void Player::Render()
{
	super::Render();
}


//void Player::LoadPlayerStat(const char* _pPath)
//{
//	FILE* pFile = nullptr;
//
//	fopen_s(&pFile, _pPath, "rt");
//
//	if (!pFile)
//	{
//		cerr << "FAILED TO LOAD PLAYERSTAT.txt";
//		__debugbreak();
//	}
//
//	char cBuffer[MAX_BUFFER_LEN] = {};
//	char* pToken = {};
//	char* pContext = {};
//	size_t szLen = fread(cBuffer, sizeof(char), MAX_BUFFER_LEN, pFile);
//	if (szLen == 0) {
//		cerr << "No file at: " << _pPath;
//		__debugbreak();
//	}
//
//	pToken = strtok_s(cBuffer, "\n", &pContext);
//
//	while (pToken) {
//		char pHeader[MAX_HEADER_LEN] = {};
//		sscanf_s(pToken, "%s", pHeader, MAX_HEADER_LEN);
//
//		if (!strcmp(pHeader, "iHP")) {
//			sscanf_s(pToken, "iHP = %d", &m_tInfo.iHP);
//		}
//		else if (!strcmp(pHeader, "iMP")) {
//			sscanf_s(pToken, "iMP = %d", &m_tInfo.iMP);
//		}
//		else if (!strcmp(pHeader, "iAttack")) {
//			sscanf_s(pToken, "iAttack = %d", &m_tInfo.iAttack);
//		}
//		else if (!strcmp(pHeader, "iDefense")) {
//			sscanf_s(pToken, "iDefense = %d", &m_tInfo.iDefense);
//		}
//		else if (!strcmp(pHeader, "iCritRate")) {
//			sscanf_s(pToken, "iCritRate = %d", &m_tInfo.iCritRate);
//		}
//		else if (!strcmp(pHeader, "iCritDmg")) {
//			sscanf_s(pToken, "iCritDmg = %d", &m_tInfo.iCritDmg);
//		}
//
//		pToken = strtok_s(nullptr, "\n", &pContext);
//	}
//
//
//	fclose(pFile);
//}