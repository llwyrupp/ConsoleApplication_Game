#pragma once
#ifndef __OBJECTMGR_H__
#define __OBJECTMGR_H__
#include "EngineCommon/Engine_Includes.h"

BEGIN(System)

class Actor;
class ENGINE_DLL ObjectMgr
{
public:
	ObjectMgr();
	~ObjectMgr();
public:
	inline static ObjectMgr& Get_Instance() { return *m_pInstance; }
public:
	void AddActor(Actor* _pActor);
	void SetPlayer(Actor* _pPlayer);
public:
	inline const vector<Actor*>& GetActors() const { return m_vecActors; }
	inline const Actor& GetPlayer() const { return *m_pPlayer; }
private:
	static ObjectMgr* m_pInstance;
private:
	vector<Actor*> m_vecActors;
	Actor* m_pPlayer = nullptr;
};

END
#endif