#include "Game/Game.h"
#include "Level/FieldLevel/FieldLevel.h"
//#include "Level/FieldLevel/FieldLevel.h"

USING(System)

Game* Game::m_pInstance = nullptr;

Game::Game()
{
	m_pInstance = this;
	m_vecLevels.clear();
	m_vecLevels.reserve(static_cast<size_t>(E_LEVEL_TYPE::E_LEVELTYPE_MAX));

	//push levels
	m_vecLevels.emplace_back(new FieldLevel());
	m_eLevelType = E_LEVEL_TYPE::E_LEVELTYPE_FIELD;

	m_pMainLevel = *(m_vecLevels.begin());
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

