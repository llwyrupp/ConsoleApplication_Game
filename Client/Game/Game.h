#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include "ClientCommon/Client_Enum.h"
#include "Engine/Engine.h"


using namespace System;

class Enemy;
class BattlePlayer;
class Game : public Engine
{
public:
	Game();
	~Game();
public:
	static Game& Get_Instance();
	const E_LEVEL_TYPE& GetCurLevelType() const { return m_eLevelType; }
	const void SetCurLevelType(const E_LEVEL_TYPE& _lType) { m_eLevelType = _lType; }
	void AddNewLevel(Level* pNewLevel);
	void ToggleLevel(E_LEVEL_TYPE _eSwitchToLevelType);
	const void EraseLevel (const Level* pLevel);
public:
	inline void SetCurEnemy(Enemy*& pEnemy) { m_pCurBattleEnemy = pEnemy; }
	inline Enemy* GetEnemy() { return m_pCurBattleEnemy; }
	inline static void SetBattlePlayer(BattlePlayer*& _pPlayer) { m_pBattlePlayer = _pPlayer; }
	inline BattlePlayer*& GetBattlePlayer() const { return m_pBattlePlayer; }//get the origin of dereference instance.
	inline void SetEnemyCnt(int _iCnt) { m_iEnemyCnt = _iCnt; }
	inline const int& GetEnemyCnt() const { return m_iEnemyCnt; }
	inline void SetIsInBattle(bool _bFlag) { m_bIsInBattle = _bFlag; }
	inline const bool& GetIsInBattle() const { return m_bIsInBattle; }
public:
	Level* GetLevel(int _iIndex);
private:
	//manages all levels
	vector<Level*>m_vecLevels;
	E_LEVEL_TYPE m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_NONE;
private:
	static Game* m_pInstance;
private:
	Enemy* m_pCurBattleEnemy = nullptr;
	static BattlePlayer* m_pBattlePlayer;

private:
	int m_iEnemyCnt = 0;
private:
	bool m_bIsInBattle = false;
};

#endif