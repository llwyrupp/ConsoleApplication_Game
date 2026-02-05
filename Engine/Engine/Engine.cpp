#include "EngineCommon/Engine_Includes.h"
#include "Engine.h"
#include "Level/Level.h"
#include "InputMgr/InputMgr.h"
#include "Graphics/Renderer/Renderer.h"
#include "CollisionManager/CollisionMgr.h"
#include "Util/Util.h"

BEGIN(System)


Engine::Engine()
{
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

	//set random seed
	
}

Engine::~Engine()
{
	Safe_Delete(m_pMainLevel);
	Safe_Delete(m_pInput);
	Safe_Delete(m_pRenderer);
}

void Engine::Run()
{
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

}

void Engine::LoadSetting()
{
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


END