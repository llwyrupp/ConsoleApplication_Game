#include "ClientCommon/Client_Includes.h"
#include "Level/MenuLevel/MenuLevel.h"

USING(System)

MenuLevel::MenuLevel()
	:m_iCurMenuIdx(0)
{
	m_vecMenuObjects.clear();
	m_vecMenuObjects.reserve(static_cast<size_t>(E_MENUOBJ_TYPE::E_MENUOBJ_MAX));
	//insert menuobjects here

	m_vecMenuObjects.emplace_back(new MENUOBJECT(
		"START GAME", []() {
			
		}));
}

MenuLevel::~MenuLevel()
{
	for (auto& menuObj : m_vecMenuObjects) {
		Safe_Delete(menuObj);
	}

	m_vecMenuObjects.clear();
}

void MenuLevel::BeginPlay()
{
	super::BeginPlay();
}

void MenuLevel::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void MenuLevel::Render()
{
	super::Render();
}

