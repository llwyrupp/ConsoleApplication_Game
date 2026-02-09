#pragma once
#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "EngineCommon/Engine_Includes.h"
#include "EngineCommon/RTTI.h"

BEGIN(System)
class Actor;

class ENGINE_DLL Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

public:
	//pure virtuals
	virtual void BeginPlay() = 0;
	virtual void Tick(float _fDeltaTime) = 0;
	virtual void Render() = 0;

public:
	void AddNewActor(Actor* pNewActor);
	void Process_AddNDestroyActors();

	inline const vector<Actor*>& GetActors() const { return m_vecActors; }
	inline Actor* GetPlayer() const { return m_pPlayer; }
protected:
	vector<Actor*> m_vecActors;
	vector<Actor*> m_vecAddReqActors;
	Actor* m_pPlayer = nullptr;
};

END
#endif