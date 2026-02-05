#pragma once
#include "EngineCommon/Engine_Includes.h"
#include "EngineCommon/Singleton.h"

BEGIN(System)
	class InputMgr;
	class Renderer;
	class CollisionMgr;
	class ENGINE_DLL Engine : public Singleton<Engine>
	{
		//grant the base class asccess to private parts
		//friend class Singleton<Engine>;

		typedef struct tagEngineSetting {
			//frame speed.
			float fFrameRate = 0.f;
			int iWidth = 0;
			int iHeight = 0;
		}ENGINESETTING;

	public:
		//CONSTRUCTOR/DESTRUCTOR
		Engine();
		virtual ~Engine();

	public:
		void Run();
		void QuitEngine();
		void SetNewLevel(class Level* pNewLevel);
		void ShutDown();
		void LoadSetting();
	public:
		inline int GetWidth() const { return m_stSetting.iWidth; }
		inline int GetHeight() const { return m_stSetting.iHeight; }
	protected:
		void BeginPlay();
		void Tick(float _fDeltaTime);
		void Render();

	protected:
		bool m_bIsQuit = false;
	protected:
		ENGINESETTING m_stSetting;
		InputMgr* m_pInput = nullptr;
		Renderer* m_pRenderer = nullptr;
		CollisionMgr* m_pCollisionMgr = nullptr;
		class Level* m_pMainLevel = nullptr;
	};
END