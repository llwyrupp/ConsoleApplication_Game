#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include "ClientCommon/Client_Includes.h"
#include "Engine/Engine.h"

USING(System)
class CollisionMgr;
class Game : public Engine
{
public:
	Game();
	~Game();
public:
	static Game& Get_Instance();
	const E_LEVEL_TYPE& GetCurLevelType() const { return m_eLevelType; }
private:
	//manages all levels
	vector<Level*>m_vecLevels;
	E_LEVEL_TYPE m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_NONE;
private:
	static Game* m_pInstance;
};

#endif