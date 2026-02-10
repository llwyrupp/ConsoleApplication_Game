#pragma once
#ifndef __GEAR_H__
#define __GEAR_H__

#include "Actor/Actor.h"

using namespace System;
class Gear : public System::Actor
{
	RTTI_DECLARATIONS(Gear, Actor)
public:
	Gear();
	virtual ~Gear();
private:

};

#endif