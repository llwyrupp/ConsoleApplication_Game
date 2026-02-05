#pragma once
#include "EngineCommon/Engine_Includes.h"
#include "EngineCommon/Singleton.h"

class ScrollMgr : public Singleton<ScrollMgr>
{
public:
	ScrollMgr();
	~ScrollMgr();

public:
	//SETTER
	void Add_ScrollX(const float _fScrollX) { m_fScrollX += _fScrollX; }
	void Add_ScrollY(const float _fScrollY) { m_fScrollY += _fScrollY; }

	//GETTER
	inline float Get_ScrollX() const { return m_fScrollX; }
	inline float Get_ScrollY() const { return m_fScrollY; }
private:
	float m_fScrollX = 0.f;
	float m_fScrollY = 0.f;
};

