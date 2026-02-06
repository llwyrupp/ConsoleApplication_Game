#include "Level/FieldLevel/FieldLevel.h"
#include "Actor/MapComponents/Ground/Ground.h"
#include "Actor/MapComponents/Wall/Wall.h"
#include "Actor/Player/Player.h"

USING(System)
FieldLevel::FieldLevel()
{
#ifdef _DEBUG
	LoadMap("../Data/Map/Field1.txt");//debug mode
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

	//파일크기를 가져오기 위해 포인터를 파일 끝으로 이동
	fseek(pFile, 0, SEEK_END);
	//char은 1바이트 크기이므로 파일크기는 텍스트 내 char의 갯수와 동일
	size_t szFileSize = ftell(pFile);
	//포인터 위치 초기화
	rewind(pFile);
	//파일 크기에 맞춰 동적버퍼 생성
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
		//case 'E'://enemy
		//	break;
		default:
			break;
		}

		++vPos.m_iX;
	}
	Safe_Delete_Arr(pBuffer);
	fclose(pFile);
}

