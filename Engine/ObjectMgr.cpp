#include "ObjectMgr.h"

BEGIN(System)
ObjectMgr* ObjectMgr::m_pInstance = nullptr;

ObjectMgr::ObjectMgr()
{
}

ObjectMgr::~ObjectMgr()
{
}

void ObjectMgr::AddActor(Actor* _pActor)
{
	m_vecActors.emplace_back(_pActor);
}

void ObjectMgr::SetPlayer(Actor* _pPlayer)
{
	m_pPlayer = _pPlayer;
}


END