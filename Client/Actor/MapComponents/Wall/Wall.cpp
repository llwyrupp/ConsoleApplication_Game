#include "Wall.h"

Wall::Wall(const Vector2& vPos)
	:super("#", nullptr, vPos, Color::eWhite)
{
	m_iSortingOrder = 0;
}

Wall::~Wall()
{

}

void Wall::BeginPlay()
{
	super::BeginPlay();
}

void Wall::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void Wall::Render()
{
	super::Render();
}

