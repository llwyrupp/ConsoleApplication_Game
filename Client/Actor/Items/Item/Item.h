#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "ClientCommon/Client_Includes.h"
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

#endif