#include "ClientCommon/Client_Enum.h"
#include "ClientCommon/Client_Defines.h"
#include "EngineCommon/Engine_Function.h"
#include "Level/MenuLevel/MenuLevel.h"
#include "InputMgr/InputMgr.h"
#include "Game/Game.h"
#include "Graphics/Renderer/Renderer.h"

using namespace System;

MenuLevel::MenuLevel()
	:m_iCurMenuIdx(0)
{
	m_vecMenuObjects.clear();
	m_vecMenuObjects.reserve(static_cast<size_t>(E_MENUOBJ_TYPE::E_MENUOBJ_MAX));
	//insert menuobjects here

	m_vecMenuObjects.emplace_back(new MENUOBJECT(
		"START GAME", []() {
			Game::Get_Instance().ToggleLevel(E_LEVEL_TYPE::E_LEVELTYPE_FIELD);
		}));

	m_vecMenuObjects.emplace_back(new MENUOBJECT(
		"END GAME", []() {
			Game::Get_Instance().QuitEngine();
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

	// 입력 처리 (방향키 위/아래키, 엔터키, ESC키).
	// 배열 길이.
	static int length = static_cast<int>(m_vecMenuObjects.size());
	if (InputMgr::Get_Instance().GetKeyDown(VK_UP))
	{
		// 인덱스 돌리기 (위 방향으로).
		m_iCurMenuIdx = (m_iCurMenuIdx - 1 + length) % length;
	}

	if (InputMgr::Get_Instance().GetKeyDown(VK_DOWN))
	{
		// 인덱스 돌리기.
		m_iCurMenuIdx = (m_iCurMenuIdx + 1) % length;
	}

	if (InputMgr::Get_Instance().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장한 함수 포인터 호출.
		m_vecMenuObjects[m_iCurMenuIdx]->fcOnSelected();
	}

	//if (InputMgr::Get_Instance().GetKeyDown(VK_ESCAPE))
	//{
	//	// 메뉴 토글.
	//	Game::Get_Instance().ToggleLevel();

	//	// 인덱스 초기화.
	//	m_iCurMenuIdx = 0;
	//}
}

void MenuLevel::Render()
{
	Renderer::Get_Instance().Submit("RPG Game", Vector2::Zero);

	// 메뉴 아이템 출력.
	for (int ix = 0; ix < static_cast<int>(m_vecMenuObjects.size()); ++ix)
	{
		// 아이템 색상 확인 (선택됐는지 여부).
		Color textColor =
			(ix == m_iCurMenuIdx) ? m_eSelectedColor : m_eUnselectedColor;

		Renderer::Get_Instance().Submit(
			m_vecMenuObjects[ix]->pText,
			Vector2(0, 2 + ix),
			textColor
		);

		// 색상 설정.
		//Util::SetConsoleTextColor(textColor);

		// 텍스트 출력.
		//std::cout << items[ix]->text << "\n";
	}
}

