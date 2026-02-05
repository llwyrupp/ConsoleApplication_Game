#pragma once
#include "EngineCommon/Engine_Defines.h"
#include "Actor/Actor.h"

USING(System)

class Item : public Actor
{

	RTTI_DECLARATIONS(Item, Actor)
public:
	Item();
	virtual ~Item();

private:
	
};

