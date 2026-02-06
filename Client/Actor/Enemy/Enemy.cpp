#include "Enemy.h"

Enemy::Enemy()
{
	m_iSortingOrder = 4;
}

Enemy::~Enemy()
{
}

void Enemy::BeginPlay()
{
	super::BeginPlay();
}

void Enemy::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void Enemy::Render()
{
	super::Render();
}

