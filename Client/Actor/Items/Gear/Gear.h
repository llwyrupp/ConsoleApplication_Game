#pragma once
#ifndef __GEAR_H__
#define __GEAR_H__

#include "ClientCommon/Client_Includes.h"
#include "Actor/Actor.h"

USING(System)
class Gear : public Actor
{
	RTTI_DECLARATIONS(Gear, Actor)
public:
	Gear();
	virtual ~Gear();
private:

};

#endif