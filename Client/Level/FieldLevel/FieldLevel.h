#pragma once
#ifndef __FIELDLEVEL_H__
#define __FIELDLEVEL_H__
#include "Interface/ICanPlayerMove.h"
#include "Level/Level.h"

using namespace System; 
class FieldLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(FieldLevel, Level)
public:
	FieldLevel();
	virtual ~FieldLevel();

	virtual bool CanMove(const Vector2& playerPosition, const Vector2& nextPosition) override;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
public:
	void LoadMap(const char* pPath);
	void CheckCollisions();
	void CheckGameOver();

public:
	inline void SetHasPlayerEscaped(bool _bFlag) { m_fAccEscapeTime = 0.f, m_bHasPlayerEscaped = _bFlag; }
private:
	bool m_bIsGameClear = false;
	bool m_bHasPlayerEscaped = false;
private:
	float m_fAccEscapeTime = 0.f;
	static float s_DelayEscapeTime;
};
#endif