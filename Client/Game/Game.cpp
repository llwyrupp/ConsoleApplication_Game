#include "Game/Game.h"
#include "Level/FieldLevel/FieldLevel.h"
#include "Level/BattleLevel/BattleLevel.h"
#include "Level/MenuLevel/MenuLevel.h"
#include "Util/Util.h"
#include "EngineCommon/Engine_Function.h"
#include "Actor/BattlePlayer/BattlePlayer.h"
#include "Actor/Player/Player.h"

using namespace System;

Game* Game::m_pInstance = nullptr;
BattlePlayer* Game::m_pBattlePlayer = nullptr;

Game::Game()
{
	m_pInstance = this;

	m_pBattlePlayer = new BattlePlayer();
	CheckIfNullReturn(m_pBattlePlayer);

	m_vecLevels.clear();
	m_vecLevels.reserve(static_cast<size_t>(E_LEVEL_TYPE::E_LEVELTYPE_MAX));

	//push levels
	m_vecLevels.emplace_back(new MenuLevel());//index 0
	m_vecLevels.emplace_back(new FieldLevel());//index 1
	//m_vecLevels.emplace_back(new BattleLevel(
	//	"../Data/Battle/BattleZombie.txt",
	//	"../Data/Player/PlayerActions.txt",
	//	"../Data/Player/PlayerItems.txt"));//index 2
	m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_FIELD;

#ifdef _DEBUG
	m_pMainLevel = m_vecLevels[1];//fieldlevel
#else
	m_pMainLevel = m_vecLevels[1];//fieldlevel
	//m_pMainLevel = *(m_vecLevels.begin());//menulevel
#endif
	Util::SetRandomSeed();
}

Game::~Game()
{
	//prevent double delete
	m_pMainLevel = nullptr;

	for (auto& level : m_vecLevels) {
		Safe_Delete(level);
	}

	m_vecLevels.clear();
}

Game& Game::Get_Instance()
{
	if (!m_pInstance) {
		cerr << "GAME INSTANCE is NULL";
		__debugbreak();
	}

	return *m_pInstance;
}

void Game::AddNewLevel(Level* pNewLevel)
{
	m_vecLevels.emplace_back(pNewLevel);
}

void Game::ToggleLevel(E_LEVEL_TYPE _eSwitchToLevelType)
{
	if (m_eLevelType == _eSwitchToLevelType)
		return;
	
	//clear screen
	//system("cls");

	switch (m_eLevelType)
	{
	case E_LEVEL_TYPE::E_LEVELTYPE_MENU:
		if (_eSwitchToLevelType == E_LEVEL_TYPE::E_LEVELTYPE_BATTLE)
		{
			//switch to battlelevel
			m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_BATTLE;
		}
		else if (_eSwitchToLevelType == E_LEVEL_TYPE::E_LEVELTYPE_FIELD)
		{
			//switch to fieldlevel
			m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_FIELD;
		}
		break;
	case E_LEVEL_TYPE::E_LEVELTYPE_FIELD:
		if (_eSwitchToLevelType == E_LEVEL_TYPE::E_LEVELTYPE_BATTLE)
		{
			//switch to battlelevel
			m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_BATTLE;
		}
		else if (_eSwitchToLevelType == E_LEVEL_TYPE::E_LEVELTYPE_MENU)
		{
			//switch to menulevel
			m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_MENU;
		}
		break;
	case E_LEVEL_TYPE::E_LEVELTYPE_BATTLE:
		if (_eSwitchToLevelType == E_LEVEL_TYPE::E_LEVELTYPE_MENU)
		{
			//switch to menulevel
			m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_MENU;
		}
		else if (_eSwitchToLevelType == E_LEVEL_TYPE::E_LEVELTYPE_FIELD)
		{
			m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_FIELD;
		}
		break;
	}

	//set mainlevel.
	m_pMainLevel = m_vecLevels[static_cast<int>(m_eLevelType)];
}

const void Game::EraseLevel(const Level* pLevel)
{
	for (int i = 0; i < m_vecLevels.size(); ++i)
	{
		if (pLevel->Is(m_vecLevels[i]))
		{
			Safe_Delete(m_vecLevels[i]);
			m_vecLevels.erase(m_vecLevels.begin() + i);
			continue;
		}
	}
}

Level* Game::GetLevel(int _iIndex)
{
	if (_iIndex >= m_vecLevels.size())
		return nullptr;

	return m_vecLevels[_iIndex];
}
