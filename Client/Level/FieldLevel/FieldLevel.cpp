#include "Level/FieldLevel/FieldLevel.h"
#include "Actor/MapComponents/Ground/Ground.h"
#include "Actor/MapComponents/Wall/Wall.h"
#include "Actor/Player/Player.h"
#include "../Client/Actor/Enemy/Enemy.h"
#include "../Engine/CollisionManager/CollisionMgr.h"

USING(System)
FieldLevel::FieldLevel()
{
#ifdef _DEBUG
	LoadMap("../Data/Map/Field1.txt");//debug mode

	//Array Decay(?): When you pass a char[] into a function, C++ automatically converts it into a char*.
	//AddNewActor(new Player(Vector2::Zero));

	//TODO: to be deleted.
	//AddNewActor(new Enemy("&", nullptr, Vector2(20, 20), Color::eRed,
	//	//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
	//	"../Data/Enemy/slime.txt", "Slime",100,10,5));
#elif
	LoadMap();//release mod.
#endif
}

FieldLevel::~FieldLevel()
{
}

bool FieldLevel::CanMove(const Vector2& playerPosition, const Vector2& nextPosition)
{
	return false;
}

void FieldLevel::BeginPlay()
{
	super::BeginPlay();
}

void FieldLevel::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
}

void FieldLevel::Render()
{
	super::Render();
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
			AddNewActor(new Enemy("&", nullptr, vPos, Color::eRed,
				//"../Data/Enemy/villager1.txt", "Villager1",100,10,5));
				"../Data/Enemy/slime.txt", "Slime", 100, 10, 5));
			AddNewActor(new Ground(vPos));
			break;
		default:
			break;
		}

		++vPos.m_iX;
	}
	Safe_Delete_Arr(pBuffer);
	fclose(pFile);
}

void FieldLevel::CheckCollisions()
{
	list<Actor*> m_listDstActors;
	list<Actor*> m_listSrcActors;
	//store playertype actor
	for (auto& actor : m_vecActors) {
		if (actor->IsTypeOf<Player>()) {
			m_listDstActors.emplace_back(actor);
			break;
		}
	}

	for (auto& actor : m_vecActors) {
		if (actor->IsTypeOf<Enemy>()) {
			m_listSrcActors.emplace_back(actor);
		}
	}



	CollisionMgr::Get_Instance().CheckCol_Player_Enemy(m_listDstActors, m_listSrcActors);
}

