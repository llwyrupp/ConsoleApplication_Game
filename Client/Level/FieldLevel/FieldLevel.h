#pragma once
#ifndef __FIELDLEVEL_H__
#define __FIELDLEVEL_H__
#include "ClientCommon/Client_Includes.h"
#include "Interface/ICanPlayerMove.h"
#include "Level/Level.h"

USING(System)
class FieldLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(FieldLevel, Level)
public:
	FieldLevel();
	virtual ~FieldLevel();

	bool CanMove(const Vector2& playerPosition, const Vector2& nextPosition) override;

public:
	void BeginPlay() override;
	void Tick(float _fDeltaTime) override;
	void Render() override;
public:
	void LoadMap(const char* pPath = nullptr);
};
#endif