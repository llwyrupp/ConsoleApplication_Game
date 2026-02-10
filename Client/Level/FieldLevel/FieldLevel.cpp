#include "Level/FieldLevel/FieldLevel.h"
#include "Actor/MapComponents/Ground/Ground.h"
#include "Actor/MapComponents/Wall/Wall.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Enemy.h"
#include "CollisionMgr/CollisionMgr.h"
#include "Game/Game.h"
#include "Level/BattleLevel/BattleLevel.h"
#include "Util/Util.h"
#include "Actor/Actor.h"
#include "EngineCommon/Engine_Function.h"
#include "Actor/BattlePlayer/BattlePlayer.h"
#include "Actor/Target.h"
#include "Graphics/Renderer/Renderer.h"

using namespace System;

FieldLevel::FieldLevel()
{
#ifdef _DEBUG
	LoadMap("../Data/Map/Field3.txt");//debug mode
	
	//Array Decay(?): When you pass a char[] into a function, C++ automatically converts it into a char*.
	//AddNewActor(new Player(Vector2::Zero));

	//TODO: to be deleted.
	//AddNewActor(new Enemy("&", nullptr, Vector2(20, 20), Color::eRed,
	//	//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
	//	"../Data/Enemy/slime.txt", "Slime",100,10,5));

	//read player stat from file.
	
#elif
	LoadMap();//release mod.
#endif
}

FieldLevel::~FieldLevel()
{

}

bool FieldLevel::CanMove(const Vector2& playerPosition, const Vector2& nextPosition)
{
	//loop through all actors.

	//vector<Actor*> vecEnemies;
	////store all Enemy-type actors inside a vector.
	//for (auto& const actor : m_vecActors) {
	//	if (actor->IsTypeOf<Enemy>()) {
	//		vecEnemies.emplace_back(actor);
	//	}
	//}

	////loop thru all enemies, see if an enemy stand in the way.
	//for (auto& const enemy : vecEnemies) {
	//	if (enemy->GetPos() == nextPosition) {
	//		return false;
	//	}
	//}

	//if there is no enemy, see if the next position is either a wall or just a ground.
	for (auto& const actor : m_vecActors) {
		if (actor->IsTypeOf<Wall>() && actor->GetPos() == nextPosition) {
			return false;//cannot move through walls.
		}
		if (actor->IsTypeOf<Ground>() && actor->GetPos() == nextPosition) {
			return true;//can move onto grounds.
		}
	}

	return false;
}

void FieldLevel::BeginPlay()
{
	super::BeginPlay();
}

void FieldLevel::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);

	if(!Game::Get_Instance().GetIsInBattle())
		CheckCollisions();
}

void FieldLevel::Render()
{
	super::Render();

	string tempStr = "Remaining Enemies: " + to_string(Game::Get_Instance().GetEnemyCnt());
	Renderer::Get_Instance().Submit(tempStr, Vector2(40, 0), Color::eWhite);

	if (m_bIsGameClear)
	{
		Util::SetConsolePos(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::eWhite);
		std::cout << "Game Clear!";
	}
}

void FieldLevel::LoadMap(const char* pPath /*= nullptr*/)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pPath, "rt");

	//exception err
	if (!pFile) {
		cerr << "FAILED TO LOAD MAP";
		__debugbreak();
	}

	fseek(pFile, 0, SEEK_END);
	size_t szFileSize = ftell(pFile);
	rewind(pFile);
	char* pBuffer = new char[szFileSize + 1];

	size_t szLen = fread(pBuffer, sizeof(char), szFileSize, pFile);

	int iIndex = 0;
	Vector2 vPos;
	int iEnemyCnt = 0;
	//read the file char by char.
	while (iIndex < szFileSize) {
		char cLetter = pBuffer[iIndex++];

		if (cLetter == '\n') {
			//update pos.
			vPos.m_iX = 0, ++vPos.m_iY;
			//skip CRLF.
			continue;
		}

		switch (cLetter)
		{
		case '#':
			AddNewActor(new Wall(vPos));
			break;
		case '.':
			AddNewActor(new Ground(vPos));
			break;
		case 'P'://player
			AddNewActor(new Player(vPos));
			AddNewActor(new Ground(vPos));
			break;
		case 'E'://enemy
			//TODO: Generate random enemy type.
			++iEnemyCnt;
#ifdef _DEBUG
			AddNewActor(new Enemy("S", nullptr, vPos, Color::eRed,
					//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
					"../Data/Enemy/slime.txt", "Slime", 100, 5, 5, E_ENEMY_TYPE::E_ENEMY_SLIME));
#elif
			
			//int iRandNum = Util::RandomInt(0, 3);
			//if (iRandNum == 0) {
			//	AddNewActor(new Enemy("S", nullptr, vPos, Color::eRed,
			//		//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
			//		"../Data/Enemy/slime.txt", "Slime", 100, 10, 5, E_ENEMY_TYPE::E_ENEMY_SLIME));
			//}
			//else if (iRandNum == 1) {
			//	AddNewActor(new Enemy("V", nullptr, vPos, Color::eRed,
			//		//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
			//		"../Data/Enemy/slime.txt", "Villager", 200, 15, 20, E_ENEMY_TYPE::E_ENEMY_VILLAGER));
			//}
			//else if (iRandNum == 2) {
			//	AddNewActor(new Enemy("Z", nullptr, vPos, Color::eRed,
			//		//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
			//		"../Data/Enemy/slime.txt", "Zombie", 300, 20, 15, E_ENEMY_TYPE::E_ENEMY_ZOMBIE));
			//}
#endif
			AddNewActor(new Ground(vPos));

			break;

		case 'T':
			AddNewActor(new Target(vPos));
			AddNewActor(new Ground(vPos));
			break;
		}

		++vPos.m_iX;
	}

	Game::Get_Instance().SetEnemyCnt(iEnemyCnt);

	Safe_Delete_Arr(pBuffer);
	fclose(pFile);
}

void FieldLevel::CheckCollisions()
{
	list<Actor*> m_listPlayer;
	list<Actor*> m_listEnemies;
	list<Actor*> m_listTargets;
	//store playertype actor
	for (auto& actor : m_vecActors) {
		if (actor->IsTypeOf<Player>()) {
			m_listPlayer.emplace_back(actor);
			break;
		}
	}

	for (auto& actor : m_vecActors) {
		if (actor->IsTypeOf<Enemy>()) {
			m_listEnemies.emplace_back(actor);
		}
		else if (actor->IsTypeOf<Target>()) {
			m_listTargets.emplace_back(actor);
		}
	}

	Enemy* pEnemy = nullptr;
	if (pEnemy = dynamic_cast<Enemy*>(System::CollisionMgr::Get_Instance().CheckCol_Player_Enemy(m_listPlayer, m_listEnemies)))
	{

		//start battlesystem
		//Game::Get_Instance().ToggleLevel(E_LEVEL_TYPE::E_LEVELTYPE_BATTLE);
		BattleLevel* pLevel = new BattleLevel(
			"../Data/Battle/BattleZombie.txt",
			"../Data/Player/PlayerActions.txt",
			"../Data/Player/PlayerItems.txt");
		Game::Get_Instance().AddNewLevel(pLevel);
		Game::Get_Instance().SetMainLevel(pLevel);
		Game::Get_Instance().SetCurLevelType(E_LEVEL_TYPE::E_LEVELTYPE_BATTLE);
		Game::Get_Instance().SetCurEnemy(pEnemy);
	}

	if (System::CollisionMgr::Get_Instance().CheckCol_Player_Enemy(m_listPlayer, m_listTargets))
	{
		//start battlesystem
		CheckGameOver();
	}
}

void FieldLevel::CheckGameOver()
{
	if (Game::Get_Instance().GetEnemyCnt() == 0)
	{
		m_bIsGameClear = true;
	}
}

