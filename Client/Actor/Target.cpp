#include "Target.h"

Target::Target(const Vector2& position)
	: super("T", nullptr, position, Color::eGreen)
{
	// 그리기 우선순위 설정.
	m_iSortingOrder = 3;
}

void Target::BeginPlay()
{
	super::BeginPlay();
}

void Target::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void Target::Render()
{
	super::Render();
}
