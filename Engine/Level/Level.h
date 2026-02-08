#pragma once
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

protected:
	vector<Actor*> m_vecActors;
	vector<Actor*> m_vecAddReqActors;
};

END