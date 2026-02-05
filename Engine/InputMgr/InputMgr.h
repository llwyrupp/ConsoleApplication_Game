#pragma once
#include "EngineCommon/Engine_Includes.h"
#include "EngineCommon/Singleton.h"

BEGIN(System)

#define MAX_SIZE_KEYSTATE 256
	class ENGINE_DLL InputMgr : public Singleton<InputMgr>
	{
	friend class Engine;

	typedef struct tagKeyState {
		//if key is down now.
		bool bIsKeyDown = false;

		//if key WAS down previously.
		bool bWasKeyDown = false;
	}KEYSTATE;

	public:
		InputMgr();
		~InputMgr();
	public:
		// 이전에 입력이 안됐는데, 현재 입력이 됐으면 1번 호출.
		bool GetKeyDown(int iKeyCode);
		// 이전에 입력이 됐는데, 현재 입력이 취소됐으면 1번 호출.
		bool GetKeyUp(int iKeyCode);
		// 현재 눌려있으면 반복 호출.
		bool GetKey(int iKeyCode);
	private:
		//입력 처리
		void ProcessInput();
		//기존 입력 저장
		void SavePrevInputStates();
	private:
		KEYSTATE m_stKeyStates[MAX_SIZE_KEYSTATE] = {};
	};
END