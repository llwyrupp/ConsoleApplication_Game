#include "BattleLevel.h"
#include "Graphics/Renderer/Renderer.h"
#include "Game/Game.h"
#include "Util/Util.h"
#include "Actor/Player/Player.h"
#include "BattlePlayer.h"

float BattleLevel::s_fTimeDelay = 2.f;

BattleLevel::BattleLevel(const string _strPath)
{
	LoadBattleLevelTemplate(_strPath);

	AddNewActor(new BattlePlayer());
}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::BeginPlay()
{

}

void BattleLevel::Tick(float _fDeltaTime)
{
	super::Tick(_fDeltaTime);
	m_fTimeAcc += _fDeltaTime;

	if (m_fTimeAcc > s_fTimeDelay) {
		m_bIsNextSeqReady = true;
		m_fTimeAcc = 0.f;
	}

#pragma region FSM
	if (m_bIsNextSeqReady) {
		switch (m_eBattleSeq) {
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERACTION:
			PlayerAction();
			break;
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_ENEMYHIT:
			EnemyHit();
			break;
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_INTERMISSION:
			Intermission();
			break;
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_ENEMYACTION:
			EnemyAction();
			break;
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERHIT:
			PlayerHit();
			break;
		}

		//toggle
		m_bIsNextSeqReady = !m_bIsNextSeqReady;
	}
#pragma endregion FSM

	Update_PlayerStatus();
	Update_NoticeSituation();
}

void BattleLevel::Render()
{
	//render battle scene
	int iLineIdx = 0;
	for(auto& const line : m_vecBattleScene)
		Renderer::Get_Instance().Submit(line, Vector2(0, iLineIdx++), Color::eWhite, 5);


	//Notice Situation
	Renderer::Get_Instance().Submit(m_strNotiSituation, m_vPosNotiSituation, Color::eWhite, 10);
	//Render Player HP string
	Renderer::Get_Instance().Submit(m_strPlayerHP, m_vPosPlayerHP, Color::eGreen, 10);
	//Render Player MP string
	Renderer::Get_Instance().Submit(m_strPlayerMP, m_vPosPlayerMP, Color::eBlue, 10);
	//Render enemy HP string
	Renderer::Get_Instance().Submit(m_strEnemyHP, m_vPosEnemyHP, Color::eRed, 10);
}

void BattleLevel::Update_PlayerStatus()
{
	//update hp and mp bar
	Game::Get_Instance().Get_MainLevel()->GetActors();
	
}

void BattleLevel::Update_NoticeSituation()
{
	//update str

}

void BattleLevel::PlayerAction()
{
	dynamic_cast<Player*>(Game::Get_Instance().Get_MainLevel()->GetPlayer())->GetInfo().iAttack;


	//reduce sp(if necessary)
	m_strNotiSituation = "Player attacked Enemy with sword!";
}

void BattleLevel::EnemyHit()
{
	//reduce enemy hp
	m_strNotiSituation = "Enemy hit by Player! Critical Hit!";

}

void BattleLevel::Intermission()
{
	//print system string
	m_strNotiSituation = "Enemy is menacingly stepping towards you...";
	//m_strNotiSituation = "You feel an urge to run away...";
}

void BattleLevel::EnemyAction()
{
	//logic for enemy action/attacks
	m_strNotiSituation = "Enemy attacks Player with his fist!";
}

void BattleLevel::PlayerHit()
{
	//reduce player hp
	m_strNotiSituation = "Player hit by Enemy!";
}



void BattleLevel::LoadBattleLevelTemplate(const string _strPath)
{
	ifstream file(_strPath);

	if (file.is_open()) {
		int iPosY = 0;
		string tempStr = "";
		while (getline(file, tempStr)) {
			m_vecBattleScene.emplace_back(tempStr);

			//set system pos
			size_t szPosX = tempStr.find("$");
			if (szPosX != string::npos) {
				m_vPosNotiSituation.m_iX = static_cast<int>(szPosX);
				m_vPosNotiSituation.m_iY = iPosY;
			}

			//set enemy hp pos
			szPosX = tempStr.find("!");
			if (szPosX != string::npos) {
				m_vPosNotiSituation.m_iX = static_cast<int>(szPosX);
				m_vPosNotiSituation.m_iY = iPosY;
			}

			//set player hp pos
			szPosX = tempStr.find("HP");
			if (szPosX != string::npos) {
				m_vPosPlayerHP.m_iX = static_cast<int>(szPosX);
				m_vPosPlayerHP.m_iY = iPosY;
			}

			//set player mp pos
			szPosX = tempStr.find("MP");
			if (szPosX != string::npos) {
				m_vPosPlayerMP.m_iX = static_cast<int>(szPosX);
				m_vPosPlayerMP.m_iY = iPosY;
			}

			++iPosY;
		}
	}
	else {
		cerr << "FAILED TO OPEN FILE LOCATED AT: " << _strPath;
		__debugbreak();
	}
}
