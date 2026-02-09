#include "ClientCommon/Client_Includes.h"
#include "../Engine/Graphics/Renderer/Renderer.h"
#include "Game/Game.h"
#include "Enemy.h"

Enemy::Enemy(const char* pImage, const char* pPath, const Vector2& vPos, Color color,
	const char* _pBattleImagePath, const char* _pName, int _iHP, int _iAtk, int _iDef)
	:super(pImage, pPath, vPos, color)
{
	m_iSortingOrder = 4;

	/*m_pBattleImage = new char[MAX_ASCIIART_LEN];
	memset(m_pBattleImage, 0, sizeof(char) * MAX_ASCIIART_LEN);*/

	m_tInfo.pName = new char[MAX_STRING_LEN] + 1;//always include +1 for null.
	size_t szLen = strlen(_pName);
	strcpy_s(m_tInfo.pName, sizeof(m_tInfo.pName) * szLen, _pName);

	m_tInfo.iHP = _iHP;
	m_tInfo.iAttack = _iAtk;
	m_tInfo.iDefense = _iDef;

	SetBattleImage(_pBattleImagePath);
}

Enemy::~Enemy()
{
	//Safe_Delete_Arr(m_pBattleImage);
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
	//if curscene is fieldlevel
	if (Game::Get_Instance().GetCurLevelType() == E_LEVEL_TYPE::E_LEVELTYPE_FIELD) {
		super::Render();
	}
	else {
		//if current scene is battlelevel
		PrintBattleImage();
	}
}

void Enemy::SetBattleImage(const char* _pPath)
{
	ifstream file(_pPath);
	if (file.is_open()) {

		string tempStr = "";
		while (std::getline(file, tempStr))
		{
			//TODO: consider .reserve.
			m_vecBattleImg.emplace_back(tempStr);
		}
		file.close();
	}
	else {
		cerr << "FAILED TO OPEN FILE LOCATED AT: " << _pPath;
		__debugbreak();
	}
}

void Enemy::PrintBattleImage() const
{
	int iY = 0;
	for (auto& line : m_vecBattleImg) {
		Renderer::Get_Instance().Submit(line, Vector2(GetPos().m_iX, GetPos().m_iY + iY), m_eColor, m_iSortingOrder);
		++iY;
	}
}
