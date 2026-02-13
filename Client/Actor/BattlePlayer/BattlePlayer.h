#pragma once
#ifndef __BATTLEPLAYER_H__
#define __BATTLEPLAYER_H__
#include "ClientCommon/Client_Struct.h"
#include "ClientCommon/Client_Enum.h"
#include "EngineCommon/RTTI.h"
#include "Actor/Actor.h"

using namespace System;
class BattlePlayer : public Actor
{
	RTTI_DECLARATIONS(BattlePlayer, Actor)
public:
	BattlePlayer();
	virtual ~BattlePlayer();
public:
	// Inherited via Actor
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
public:
	inline const PLAYERINFO GetInfo() const { return m_tInfo; }
	inline void SetPlayerHP(int _iHP) { m_tInfo.iHP = _iHP; }
	void LoadPlayerStat(const char* _pPath);
	void SavePlayerStat(const char* _pPath);
private:
	PLAYERINFO m_tInfo = {};
private:
	static BattlePlayer* m_pInstance;
private:
	E_PLAYERACTION m_eCurPlayerAction = E_PLAYERACTION::E_PLAYERACTION_NONE;
};


#endif