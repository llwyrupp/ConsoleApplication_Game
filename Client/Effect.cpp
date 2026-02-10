#include "Effect.h"
#include "Engine/Engine.h"

static const Effect::EFFECTFRAME sequence[] =
{
	Effect::EFFECTFRAME("  @  ", 1.08f, Color::eRed),
	Effect::EFFECTFRAME(" @@  ", 1.08f, Color::eBlue),
	Effect::EFFECTFRAME(" @@@ ", 1.08f, Color::eGreen),
	Effect::EFFECTFRAME("@@@@ ", 1.08f, Color::eRed),
	Effect::EFFECTFRAME("  +1 ", 1.5f, Color::eGreen)
};

Effect::Effect(const Vector2& position)
	: super(sequence[0].frame, nullptr, position, Color::eRed)
{
	m_iSortingOrder = 100;

	int effectFrameImageLength = 6;

	int iX = GetPos().m_iX;
	int iY = GetPos().m_iY;
	SetPos(Vector2(iX < 0 ? effectFrameImageLength + iX : iX, iY));
	SetPos(Vector2(
		iX + effectFrameImageLength > Engine::Get_Instance().GetWidth() ? iX - effectFrameImageLength : iX, iY));

	m_iEffSeqCnt = sizeof(sequence) / sizeof(sequence[0]);

	m_fDelayTime = sequence[0].playTime;

	m_eColor = sequence[0].color;
}

void Effect::BeginPlay()
{
}

void Effect::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	m_fAccTime += deltaTime;
	if (m_fAccTime < m_fDelayTime)
	{
		return;
	}

	if (m_iCurSeqIdx == m_iEffSeqCnt - 1)
	{
		Destroy();
		return;
	}

	m_fAccTime = 0.f;

	++m_iCurSeqIdx;

	m_fDelayTime = sequence[m_iCurSeqIdx].playTime;

	ChangeImage(sequence[m_iCurSeqIdx].frame);

	m_eColor = sequence[m_iCurSeqIdx].color;
}

void Effect::Render()
{
	super::Render();
}
