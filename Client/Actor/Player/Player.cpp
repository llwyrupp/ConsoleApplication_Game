#include "ClientCommon/Client_Includes.h"
#include "Actor/Player/Player.h"
#include "InputMgr/InputMgr.h"

USING(System)
Player::Player(const Vector2& vPos)
	:super(nullptr, "../Data/Player/Player.txt", vPos, Color::eGreen)
{
	m_iSortingOrder = 5;
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	super::BeginPlay();
}

void Player::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);


	//Input
	//Movement
	Vector2 vNewPos = GetPos();
	if (InputMgr::Get_Instance().GetKey(VK_LEFT)) {
		vNewPos.m_iX = GetPos().m_iX - 1;
	}
	if (InputMgr::Get_Instance().GetKey(VK_RIGHT)) {
		vNewPos.m_iX = GetPos().m_iX + 1;
	}
	if (InputMgr::Get_Instance().GetKey(VK_UP)) {
		vNewPos.m_iY = GetPos().m_iY - 1;
	}
	if (InputMgr::Get_Instance().GetKey(VK_DOWN)) {
		vNewPos.m_iY = GetPos().m_iY + 1;
	}
	SetPos(vNewPos);
}

void Player::Render()
{
	super::Render();
}
