#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "ClientCommon/Client_Includes.h"
#include "Actor/Actor.h"

USING(System)
class Enemy : public Actor
{
	RTTI_DECLARATIONS(Enemy, Actor)
public:
	Enemy(const char* pImage, const char* pPath, const Vector2& vPos, Color color, //super
		const char* _pBattleImagePath, const char* _pName, int _iHP, int _iAtk, int _iDef);//Enemy::custom
	virtual ~Enemy();
public:
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
public:
	//all enemies will have ascii images in the battle scene
	void SetBattleImage(const char* _pPath);
	void PrintBattleImage() const;
protected:
	ENEMYINFO m_tInfo = {};
	//char* m_pBattleImage = nullptr;
	vector<string> m_vecBattleImg;
};


#endif