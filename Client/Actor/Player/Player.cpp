#include "ClientCommon/Client_Includes.h"
#include "Actor/Player/Player.h"
#include "InputMgr/InputMgr.h"

USING(System)
Player::Player(const Vector2& vPos)
	:super(nullptr, "../Data/Player/Player.txt", vPos, Color::eGreen), m_fSpeed(10.f), m_fAccX(0.f), m_fAccY(0.f)
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
		m_fAccX += _fDeltaTime * m_fSpeed;
		if (m_fAccX > 1.f) {
			vNewPos.m_iX = GetPos().m_iX - 1;
			m_fAccX = 0.f;
		}
	}
	if (InputMgr::Get_Instance().GetKey(VK_RIGHT)) {
		m_fAccX += _fDeltaTime * m_fSpeed;
		if (m_fAccX > 1.f) {
			vNewPos.m_iX = GetPos().m_iX + 1;
			m_fAccX = 0.f;
		}
	}
	if (InputMgr::Get_Instance().GetKey(VK_UP)) {
		m_fAccY += _fDeltaTime * m_fSpeed;
		if (m_fAccY > 1.f) {
			vNewPos.m_iY = GetPos().m_iY - 1;
			m_fAccY = 0.f;
		}
	}
	if (InputMgr::Get_Instance().GetKey(VK_DOWN)) {
		m_fAccY += _fDeltaTime * m_fSpeed;
		if (m_fAccY > 1.f) {
			vNewPos.m_iY = GetPos().m_iY + 1;
			m_fAccY = 0.f;
		}
	}
	SetPos(vNewPos);
}

void Player::Render()
{
	super::Render();
}
