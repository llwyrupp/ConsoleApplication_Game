#pragma once
#ifndef __BATTLEPLAYER_H__
#define __BATTLEPLAYER_H__
#include "EngineCommon/RTTI.h"
#include "ClientCommon/Client_Includes.h"
#include "Actor/Actor.h"

USING(System)
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
private:
	PLAYERINFO m_tInfo = {};

};


#endif