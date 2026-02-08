#include "Villager.h"

Villager::Villager()
{
	m_tInfo.iHP = 100;
	m_tInfo.iAttack = 10;
	m_tInfo.iDefense = 5;

	m_tInfo.pName = new char[MAX_STRING_LEN];
	strcpy_s(m_tInfo.pName, sizeof(char) * MAX_STRING_LEN, "Villager");
}

Villager::~Villager()
{
	Safe_Delete_Arr(m_tInfo.pName);
}

void Villager::BeginPlay()
{
	super::BeginPlay();
}

void Villager::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void Villager::Render()
{
	super::Render();
}

