#include "EngineCommon/Engine_Includes.h"
#include "Engine.h"
#include "Level/Level.h"
#include "InputMgr/InputMgr.h"
#include "Graphics/Renderer/Renderer.h"
#include "CollisionManager/CollisionMgr.h"
#include "Util/Util.h"

USING(Util)

BEGIN(System)

Engine* Engine::m_pInstance = nullptr;

Engine::Engine()
{
	m_pInstance = this;

	//create systems
	//input system
	m_pInput = new InputMgr();

	//collision manager
	m_pCollisionMgr = new CollisionMgr();

	//Load setting from setting.txt file
	LoadSetting();


	//create a renderer
	m_pRenderer = new Renderer(Vector2(m_stSetting.iWidth, m_stSetting.iHeight));
	



	//turn of cursor.
	Util::TurnOffCursor();

	//set random seed
	SetRandomSeed();
	
}

Engine::~Engine()
{
	Safe_Delete(m_pMainLevel);
	Safe_Delete(m_pInput);
	Safe_Delete(m_pRenderer);
}

void Engine::Run()
{
	LARGE_INTEGER m_Frequency;//frequency
	QueryPerformanceFrequency(&m_Frequency);

	int64_t t_curTime = 0;//(STL에서 타입재정의된 것)
	int64_t t_prevTime = 0;

	//HARDWARE TIMER로 시간 구하기
	LARGE_INTEGER m_FrameTime;//time
	QueryPerformanceCounter(&m_FrameTime);//이 함수가 실행되는 실제 시간, 하드웨어 시간

	t_curTime = m_FrameTime.QuadPart;
	t_prevTime = t_curTime;

	m_stSetting.fFrameRate = m_stSetting.fFrameRate == 0.f ? 60.f : m_stSetting.fFrameRate;
	float fOneFrameTime = 1.f / m_stSetting.fFrameRate;//1프레임당 몇 초

	//engine loop
	while (!m_bIsQuit) {
		QueryPerformanceCounter(&m_FrameTime);
		t_curTime = m_FrameTime.QuadPart;
		float fDeltaTime = static_cast<float>(t_curTime - t_prevTime);
		fDeltaTime /= static_cast<float>(m_Frequency.QuadPart);

		//고정 프레임 기법.
		if (fDeltaTime >= fOneFrameTime)
		{
			m_pInput->ProcessInput();

			BeginPlay();
			Tick(fDeltaTime);
			Render();

			t_prevTime = t_curTime;//update

			m_pInput->SavePrevInputStates();

			//레벨에 요청된 추가/제거 처리
			if(m_pMainLevel)
				m_pMainLevel->Process_AddNDestroyActors();
		}
	}
	//@TODO: 프로그램 종료
	cout << "Program Quit.\n";


	ShutDown();
}

void Engine::QuitEngine()
{
	m_bIsQuit = true;
}

void Engine::SetNewLevel(Level* pNewLevel)
{
	Safe_Delete(m_pMainLevel);
	m_pMainLevel = pNewLevel;
}

void Engine::ShutDown()
{
	TurnOnCursor();
}

void Engine::LoadSetting()
{
	m_stSetting = {};

	FILE* pFile = nullptr;
	fopen_s(&pFile, "../Config/Settings.txt", "rt");

	//exception
	if (!pFile) {
		cout << "Failed to open Settings.txt.\n";
		__debugbreak();
		return;
	}

	char cBuffer[MAX_BUFFER_LEN] = {};
	size_t szLen = fread(cBuffer, sizeof(char), MAX_BUFFER_LEN, pFile);

	//PARSING
	char* pContext = nullptr;
	char* pToken = nullptr;
	pToken = strtok_s(cBuffer, "\n", &pContext);

	while (pToken) {
		//read parameter names only
		char pHeader[MAX_HEADER_LEN] = {};

		sscanf_s(pToken, "%s", pHeader, MAX_HEADER_LEN);

		if (!strcmp(pHeader, "framerate")) {
			sscanf_s(pToken, "framerate = %f", &m_stSetting.fFrameRate);
		}
		else if (!strcmp(pHeader, "width")) {
			sscanf_s(pToken, "width = %d", &m_stSetting.iWidth);
		}
		else if (!strcmp(pHeader, "height")) {
			sscanf_s(pToken, "height = %d", &m_stSetting.iHeight);
		}

		//'\n'로 문자열 분리
		pToken = strtok_s(nullptr, "\n", &pContext);
	}

	fclose(pFile);
}

void Engine::BeginPlay()
{
	if (!m_pMainLevel) {
		cout << "m_pMainLevel is empty\n";
		return;
	}
	m_pMainLevel->BeginPlay();
}

void Engine::Tick(float _fDeltaTime)
{
	if (!m_pMainLevel) {
		cout << "m_pMainLevel is empty\n";
		return;
	}
	m_pMainLevel->Tick(_fDeltaTime);
}

void Engine::Render()
{
	if (!m_pMainLevel) {
		cout << "m_pMainLevel is empty\n";
		return;
	}
	m_pMainLevel->Render();//all actors submit to renderer.

	//then renderer draws the whole thing
	if (!m_pRenderer) {
		cout << "m_pRenderer is empty\n";
		return;
	 }

	m_pRenderer->Render();
}

Engine& Engine::Get_Instance()
{
	if (!m_pInstance) {
		cerr << "ENGINE INSTANCE is NULL";
		__debugbreak();
	}

	return *m_pInstance;
}

END