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
		static bool CheckCol_Player_Enemy(list<Actor*>& _Dst, list<Actor*>& _Src);
		static bool Check_Intersect(const RECT& _rtDst, const RECT& _rtSrc);
	private:
		static CollisionMgr* m_pInstance;
	};
}

