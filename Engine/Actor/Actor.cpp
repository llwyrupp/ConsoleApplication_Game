#include "Actor/Actor.h"
#include "Graphics/Renderer/Renderer.h"

BEGIN(System)

Actor::Actor(const char* pImage /*= " "*/, const Vector2& vPos /*= Vector2::Zero*/, Color color /*= Color::eWhite*/)
	:m_vPosition(vPos), m_eColor(color)
{
	size_t szLen = strlen(pImage) + 1;//include null.
	m_pImage = new char[szLen];
	memset(m_pImage, 0, sizeof(char) * szLen);//initialize
	strcpy_s(m_pImage, sizeof(char) * szLen, m_pImage);

	m_iStringWidth = static_cast<int>(strlen(pImage));
}

Actor::~Actor()
{
	Safe_Delete_Arr(m_pImage);
}

void Actor::BeginPlay()
{
	m_bHasBegunPlay = true;
}

void Actor::Tick(float _fDeltaTime)
{
	//TODO: Common Actor Behaviour to be added if necessary.
}

void Actor::Render()
{
	Renderer::Get_Instance().Submit(m_pImage, m_vPosition, m_eColor, m_iSortingOrder);
}

void Actor::SetPos(const Vector2& vNewPos)
{
	//변경하려는 위치가 현 위치와 동일하면 스킵.
	if (m_vPosition == vNewPos)
		return;

	//새 위치값으로 액터 위치 갱신
	m_vPosition = vNewPos;
}

END