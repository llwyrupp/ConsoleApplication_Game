#include "CollisionMgr.h"

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

void CollisionMgr::CheckCol_Player_Enemy(list<Actor*>& _Dst, list<Actor*>& _Src)
{
	vector<Actor*> vecPlayer;
}

END