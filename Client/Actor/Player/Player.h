#pragma once

#include "EngineCommon/Engine_Defines.h"
#include "Actor/Actor.h"

USING(System)

class ENGINE_DLL Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player();
	~Player();

private:
	

};

