#include "Ground.h"

Ground::Ground(const Vector2& vPos)
	:super(" ", nullptr, vPos, Color::eWhite)
{
	m_iSortingOrder = 0;
}

Ground::~Ground()
{
}

void Ground::BeginPlay()
{
	super::BeginPlay();
}

void Ground::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void Ground::Render()
{
	super::Render();
}
