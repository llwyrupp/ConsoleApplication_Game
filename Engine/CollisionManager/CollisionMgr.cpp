#include "CollisionMgr.h"
#include "../Engine/Actor/Actor.h"

BEGIN(System)

CollisionMgr* CollisionMgr::m_pInstance = nullptr;

CollisionMgr::CollisionMgr()
{
	m_pInstance = this;
}

CollisionMgr::~CollisionMgr()
{
}

CollisionMgr& CollisionMgr::Get_Instance()
{
	if (!m_pInstance) {
		cerr << "CollisionMgr INSTANCE is NULL";
		__debugbreak();
	}

	return *m_pInstance;
}

bool CollisionMgr::CheckCol_Player_Enemy(list<Actor*>& _Dst, list<Actor*>& _Src)
{
	for (auto& dst : _Dst) {
		for (auto& src : _Src) {
			if (Check_Intersect(dst->GetRect(), src->GetRect())) 
			{
				return true;
			}
		}
	}
	return false;
}

bool CollisionMgr::Check_Intersect(const RECT& _rtDst, const RECT& _rtSrc)
{
	int iMinX_Dst = _rtDst.left, iMaxX_Dst = _rtDst.right,
		iMinY_Dst = _rtDst.top, iMaxY_Dst = _rtDst.bottom,
		iMinX_Src = _rtSrc.left, iMaxX_Src = _rtSrc.right,
		iMinY_Src = _rtSrc.top, iMaxY_Src = _rtSrc.bottom;

	//check if two intersects.

	//RIGHT_BOTTOM
	if (_rtDst.right >= _rtSrc.left && _rtDst.bottom >= _rtSrc.top)
		return true;

	//LEFT_BOTTOM
	if (_rtDst.left <= _rtSrc.right && _rtDst.bottom >= _rtSrc.top)
		return true;

	//LEFT_TOP
	if (_rtDst.left <= _rtSrc.right && _rtDst.top <= _rtSrc.bottom)
		return true;

	//RIGHT_TOP
	if (_rtDst.right >= _rtSrc.left && _rtDst.top <= _rtSrc.bottom)
		return true;

	return false;
}

END