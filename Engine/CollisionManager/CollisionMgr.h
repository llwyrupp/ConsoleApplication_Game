#pragma once
#include "EngineCommon/Engine_Includes.h"

namespace System {
	class Actor;
	//manage collisions between two actors(base class of all objects)
	class ENGINE_DLL CollisionMgr
	{
		//will use SINGLETON.

	public:
		CollisionMgr();
		~CollisionMgr();

	public:
		static CollisionMgr& Get_Instance();
	public:
		static void CheckCol_Player_Enemy(list<Actor*>& _Dst, list<Actor*>& _Src);
	private:
		static CollisionMgr* m_pInstance;
	};
}

