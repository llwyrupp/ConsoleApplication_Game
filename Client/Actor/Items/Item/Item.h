#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "Actor/Actor.h"


class Item : public System::Actor
{

	RTTI_DECLARATIONS(Item, Actor)
public:
	Item();
	virtual ~Item();

private:
	
};

#endif