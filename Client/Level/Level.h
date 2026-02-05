#pragma once

#include "EngineCommon/RTTI.h"

USING(System)
class Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

public:
	virtual void BeginPlay() PURE;
	virtual void Tick(float _fDeltaTime) PURE;
	virtual void Render() PURE;
	
protected:

};

