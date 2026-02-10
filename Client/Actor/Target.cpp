#include "Target.h"

Target::Target(const Vector2& position)
	: super("T", nullptr, position, Color::eGreen)
{
	// 그리기 우선순위 설정.
	m_iSortingOrder = 3;
}

void Target::BeginPlay()
{
}

void Target::Tick(float _fDeltaTime)
{
}

void Target::Render()
{
}
