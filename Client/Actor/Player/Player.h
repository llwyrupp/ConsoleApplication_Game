#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "ClientCommon/Client_Struct.h"
#include "Actor/Actor.h"

using namespace System;

class Player : public System::Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player(const Vector2& vPos);
	virtual ~Player();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
private:
	float m_fSpeed = 0.f;
	float m_fAccX = 0.f;
	float m_fAccY = 0.f;
public:
	
private:
	//PLAYERINFO m_tInfo = {};
};

#endif