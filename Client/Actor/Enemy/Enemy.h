#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "ClientCommon/Client_Struct.h"
#include "ClientCommon/Client_Enum.h"
#include "EngineCommon/RTTI.h"
#include "Actor/Actor.h"

using namespace System;
class Enemy : public System::Actor
{
	RTTI_DECLARATIONS(Enemy, Actor)
public:
	Enemy(const char* pImage, const char* pPath, const Vector2& vPos, Color color, //super
		const char* _pBattleImagePath, const char* _pName, int _iHP, int _iAtk, int _iDef,
		E_ENEMY_TYPE _eType);//Enemy::custom
	virtual ~Enemy();
public:
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
public:
	//all enemies will have ascii images in the battle scene
	void SetBattleImage(const char* _pPath);
	void PrintBattleImage() const;
public:
	inline const ENEMYINFO& GetInfo() const { return m_tInfo; }
	inline void SetEnemyHP(int _iHP) { m_tInfo.iHP = _iHP; }
protected:
	ENEMYINFO m_tInfo = {};
	//char* m_pBattleImage = nullptr;
	vector<string> m_vecBattleImg;
	E_ENEMY_TYPE m_eEnemyType = E_ENEMY_TYPE::E_ENEMY_NONE;
};


#endif