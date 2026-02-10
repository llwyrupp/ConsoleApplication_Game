#include "BattleLevel.h"
#include "Graphics/Renderer/Renderer.h"
#include "Game/Game.h"
#include "Util/Util.h"
#include "Actor/Player/Player.h"
#include "Actor/BattlePlayer/BattlePlayer.h"
#include "Actor/Enemy/Enemy.h"
#include "EngineCommon/Engine_Function.h"
#include "Effect.h"

using namespace System;

float BattleLevel::s_fSequenceTimeDelay = 3.f;

BattleLevel::BattleLevel(const string _strPathBattleScene, const string _strPathPlayerActions, const string _strPathPlayerItems)
{
	if (Game::Get_Instance().GetBattlePlayer())
	{
		BattlePlayer* pPlayer = new BattlePlayer();
		CheckIfNullReturn(pPlayer);
		AddNewActor(pPlayer);
	}
	


	//reserve memory.
	m_vecStrPlayerActions.clear();
	m_vecStrPlayerItems.clear();
	m_vecStrPlayerActions.reserve(MAX_PLAYERACTION_SIZE);
	m_vecStrPlayerItems.reserve(MAX_PLAYERINVEN_SIZE);

	LoadBattleLevelTemplate(_strPathBattleScene, _strPathPlayerActions, _strPathPlayerItems);
	
	m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;
	m_ePlayerAction = E_PLAYERACTION::E_PLAYERACTION_NONE;

	m_pEnemy = dynamic_cast<Enemy*>(Game::Get_Instance().GetEnemy());

	Game::Get_Instance().SetIsInBattle(true);
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



	//only update time when entered a sequence and is in delay.
	if (!m_bIsNextSeqReady) {
		m_fTimeAcc += _fDeltaTime;

		if (m_fTimeAcc > s_fSequenceTimeDelay)
			m_bIsNextSeqReady = true;//move on to the next sequence.
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
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT:
			m_strNotiSituation = "Waiting for Player input...";
			break;
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_ESCAPE:
		case E_BATTLESEQUENCE::E_BATTLESEQUENCE_COMPLETE:
			Game::Get_Instance().ToggleLevel(E_LEVEL_TYPE::E_LEVELTYPE_FIELD);
			Game::Get_Instance().EraseLevel(this);
			Game::Get_Instance().SetIsInBattle(false);
			m_bIsBattleOver = true;
			break;
		}
	}
#pragma endregion FSM
	if (m_bIsBattleOver)
		return;

	Update_PlayerStatus();
	Update_EnemyStatus();
	Update_Arrow();
}

void BattleLevel::Render()
{
	//render battle scene
	int iLineIdx = 0;
	for (auto& const line : m_vecStrBattleScene)
		Renderer::Get_Instance().Submit(line, Vector2(0, iLineIdx++), Color::eWhite);


	//Notice Situation
	/*Renderer::Get_Instance().Submit(m_strNotiSituation, 
		Vector2(m_vPosNotiSituation.m_iX + static_cast<int>(m_fTimeAcc * 5), m_vPosNotiSituation.m_iY), Color::eWhite);*/
	Renderer::Get_Instance().Submit(m_strNotiSituation, m_vPosNotiSituation, Color::eWhite);
	//Render Player HP string
	Renderer::Get_Instance().Submit(m_strPlayerHP, m_vPosPlayerHP, Color::eGreen);
	//Render Player MP string
	Renderer::Get_Instance().Submit(m_strPlayerMP, m_vPosPlayerMP, Color::eBlue);
	//Render enemy HP string
	Renderer::Get_Instance().Submit(m_strEnemyHP, m_vPosEnemyHP, Color::eRed);

	if (m_ePlayerAction != E_PLAYERACTION::E_PLAYERACTION_ITEM)
	{
		//render player actions
		for (int i = 0; i < static_cast<int>(m_vecStrPlayerActions.size()); ++i)
		{
			Renderer::Get_Instance().Submit(m_vecStrPlayerActions[i], m_vPosChoice[i], Color::eWhite);
		}
	}
	else {
		//render player choice
		for (int i = 0; i < static_cast<int>(m_vecStrPlayerItems.size()); ++i)
		{
			Renderer::Get_Instance().Submit(m_vecStrPlayerItems[i], m_vPosChoice[i], Color::eWhite, 10);
		}
	}

	//render player choice arrow
	Renderer::Get_Instance().Submit(m_strInvenArrow, m_vPosArrow, Color::eGreen, 10);
}

void BattleLevel::Update_PlayerStatus()
{
	//update hp and mp bar
	BattlePlayer* pPlayer = Game::Get_Instance().GetBattlePlayer();
	CheckIfNullReturn(pPlayer);
	int iHP = static_cast<float>(pPlayer->GetInfo().iHP);
	int iMP = static_cast<float>(pPlayer->GetInfo().iMP);
	
	int iFillHP = iHP / 10;
	int iFillMP = iMP / 10;

	m_strPlayerHP = "";
	//player hp
	m_strPlayerHP = "HP [";
	for (int i = 0; i < iFillHP; ++i)
		m_strPlayerHP.append("O");
	for (int i = iFillHP; i < GAUGE_SIZE; ++i)
		m_strPlayerHP.append("-");
	m_strPlayerHP.append("] [");
	m_strPlayerHP.append(to_string(iHP));
	m_strPlayerHP.append("%]");

	

	m_strPlayerMP = "";
	//player mp
	m_strPlayerMP = "MP [";
	for (int i = 0; i < iFillMP; ++i)
		m_strPlayerMP.append("O");
	for (int i = iFillMP; i < GAUGE_SIZE; ++i)
		m_strPlayerMP.append("-");
	m_strPlayerMP.append("] [");
	m_strPlayerMP.append(to_string(iMP));
	m_strPlayerMP.append("%]");
}

void BattleLevel::Update_EnemyStatus()
{
	int iHP = static_cast<float>(Game::Get_Instance().GetEnemy()->GetInfo().iHP);

	int iFillHP = iHP / 10;

	m_strEnemyHP = "";
	//enemy hp bar
	m_strEnemyHP = "HP [";
	for (int i = 0; i < iFillHP; ++i)
		m_strEnemyHP.append("O");
	for(int i = iFillHP; i< GAUGE_SIZE; ++i)
		m_strEnemyHP.append("-");

	m_strEnemyHP.append("] [");
	m_strEnemyHP.append(to_string(iHP));
	m_strEnemyHP.append("%]");
}

void BattleLevel::Update_Arrow()
{
	//update arrow position.
	for (int i = 0; i < MAX_PLAYERACTION_SIZE; ++i) {
		if (m_iCurInventoryIndex == i) {
			m_vPosArrow = m_vPosChoice[i];
			break;
		}
	}
}

void BattleLevel::PlayerAction()
{
	switch (m_ePlayerAction) {
	case E_PLAYERACTION::E_PLAYERACTION_ATTACK:
		PlayerAttack();
		break;
	case E_PLAYERACTION::E_PLAYERACTION_GUARD:
		PlayerGuard();
		break;
	case E_PLAYERACTION::E_PLAYERACTION_ITEM:
		PlayerOpenInven();
		break;
	case E_PLAYERACTION::E_PLAYERACTION_USEITEM:
		PlayerUseItem();
		break;
	case E_PLAYERACTION::E_PLAYERACTION_RUN:
		PlayerTryRun();
		break;
	}

	//m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;
}

void BattleLevel::EnemyHit()
{
	int iRandNum = Util::RandomInt(0, 2);

	BattlePlayer* pPlayer = Game::Get_Instance().GetBattlePlayer();
	Enemy* pEnemy = Game::Get_Instance().GetEnemy();
	if (pPlayer && pEnemy) {
		int iPlayerAttack = pPlayer->GetInfo().iAttack + iRandNum;
		if (pEnemy->GetInfo().iHP - iPlayerAttack > 0) {
			pEnemy->SetEnemyHP(pEnemy->GetInfo().iHP - iPlayerAttack);
			m_strNotiSituation = "Enemy hit by Player! Enemy loses " + to_string(iPlayerAttack) + " HP!";
			m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_INTERMISSION;
		}
		else {//battle over.
			pEnemy->SetEnemyHP(0);
			int iTotalEnemies = Game::Get_Instance().GetEnemyCnt();
			iTotalEnemies = iTotalEnemies - 1 > 0 ? iTotalEnemies - 1 : 0;
			Game::Get_Instance().SetEnemyCnt(iTotalEnemies);

			pEnemy->Set_IsDestroyRequested(true);
			m_strNotiSituation = "Enemy is down! Player wins!";
			m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_COMPLETE;
		}
		//reduce enemy hp

		m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;//start delay until next sequence

		//create hit effect
		//AddNewActor(new Effect(Vector2(80, 30)));
	}
}

void BattleLevel::Intermission()
{
	//print system string
	//m_strNotiSituation = "...INTERMISSION...";
	//m_strNotiSituation = "You feel an urge to run away...";
	m_strNotiSituation = "Enemy is getting ready to take action...";
	m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_ENEMYACTION;

	//reset all actions
	m_ePlayerAction = E_PLAYERACTION::E_PLAYERACTION_NONE;
	m_eEnemyState = E_ENEMYSTATE::E_ENEMYSTATE_NONE;

	m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
}

void BattleLevel::EnemyAction()
{
	int iRandNum = Util::RandomInt(0, 1);

	switch (iRandNum) {
	case 0://ATTACK
		m_strNotiSituation = "Enemy attacks Player with his fist!";
		m_eEnemyState = E_ENEMYSTATE::E_ENEMYSTATE_ATTACK;
		m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERHIT;
		m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
		break;
	case 1://GUARD
		m_strNotiSituation = "Enemy guards up!";
		m_eEnemyState = E_ENEMYSTATE::E_ENEMYSTATE_GUARD;
		m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_PLAYERHIT;
		m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
		break;
	default:
		cout << "NO ACTION FOR THIS INDEX\n";
		break;
	}
}

void BattleLevel::PlayerHit()
{
	switch (m_eEnemyState) {
	case E_ENEMYSTATE::E_ENEMYSTATE_ATTACK:
		{
			int iRandNum = Util::RandomInt(0, 3);
			//reduce player hp
			BattlePlayer* pPlayer = Game::Get_Instance().GetBattlePlayer();
			Enemy* pEnemy = Game::Get_Instance().GetEnemy();
			if (pPlayer && pEnemy)//get player's hp, set new hp
			{
				int iEnemyAttack = pEnemy->GetInfo().iAttack + iRandNum;
				(*pPlayer).SetPlayerHP((*pPlayer).GetInfo().iHP - iEnemyAttack);
				m_strNotiSituation = "Player hit by Enemy! " + to_string(iEnemyAttack) + " Damage Taken!";
				m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;
				m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
			}
		}
		break;
	case E_ENEMYSTATE::E_ENEMYSTATE_GUARD:
		m_strNotiSituation = "Player took no damage. Enemy is still guarding up.";
		m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;
		m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
		break;
	}
}

void BattleLevel::PlayerAttack()
{
	m_strNotiSituation = "Player attacked Enemy!";

	m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_ENEMYHIT;
	m_eEnemyState = E_ENEMYSTATE::E_ENEMYSTATE_HIT;

	m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
}

void BattleLevel::PlayerGuard()
{
	m_strNotiSituation = "Player raises up his arms to guard! Defense increased!";
	m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;//wait for player input

	m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
}

void BattleLevel::PlayerOpenInven()
{
	//open up inventory
	m_strNotiSituation = "Select your item.";

	switch (m_iCurInventoryIndex) {
	case 0:

		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}

	m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;//wait for player input

	m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
}

void BattleLevel::PlayerUseItem()
{
	m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
}

void BattleLevel::PlayerTryRun()
{
	int iRandInt = Util::RandomInt(0, 100);

	if (iRandInt > 50) {
		m_strNotiSituation = "Player successfully escaped!";
		m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_COMPLETE;
	}
	else {
		m_strNotiSituation = "Player failed to flee!";
		m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;
	}

	m_fTimeAcc = 0.f, m_bIsNextSeqReady = false;
}



void BattleLevel::LoadBattleLevelTemplate(const string _strPathBattleScene, const string _strPathPlayerActions, const string _strPathPlayerItems)
{
	ifstream file(_strPathBattleScene);

	if (file.is_open()) {
		int iPosY = 0;
		string tempStr = "";
		while (getline(file, tempStr)) {
			m_vecStrBattleScene.emplace_back(tempStr);

			//set system pos
			size_t szPosX = tempStr.find("$");
			if (szPosX != string::npos) {
				m_vPosNotiSituation.m_iX = static_cast<int>(szPosX);
				m_vPosNotiSituation.m_iY = iPosY;
			}

			//set enemy hp pos
			szPosX = tempStr.find("!");
			if (szPosX != string::npos) {
				m_vPosEnemyHP.m_iX = static_cast<int>(szPosX);
				m_vPosEnemyHP.m_iY = iPosY;
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

			//set inven choice idx
			//FIRST IDX
			szPosX = tempStr.find("1>");
			if (szPosX != string::npos) {
				m_vPosChoice[0].m_iX = static_cast<int>(szPosX);
				m_vPosChoice[0].m_iY = iPosY;
			}
			//SECOND IDX
			szPosX = tempStr.find("2>");
			if (szPosX != string::npos) {
				m_vPosChoice[1].m_iX = static_cast<int>(szPosX);
				m_vPosChoice[1].m_iY = iPosY;
			}
			//THIRD IDX
			szPosX = tempStr.find("3>");
			if (szPosX != string::npos) {
				m_vPosChoice[2].m_iX = static_cast<int>(szPosX);
				m_vPosChoice[2].m_iY = iPosY;
			}
			//FOURTH IDX
			szPosX = tempStr.find("4>");
			if (szPosX != string::npos) {
				m_vPosChoice[3].m_iX = static_cast<int>(szPosX);
				m_vPosChoice[3].m_iY = iPosY;
			}

			++iPosY;
		}
	}
	else {
		cerr << "FAILED TO OPEN FILE LOCATED AT: " << _strPathBattleScene;
		__debugbreak();
	}

	file.close();

	//player action strings
	ifstream file2(_strPathPlayerActions);
	if (file2.is_open()) {
		string tempStr = "";
		while (getline(file2, tempStr))
		{
			m_vecStrPlayerActions.emplace_back(tempStr);
		}
	}
	else {
		cerr << "FAILED TO OPEN FILE LOCATED AT: " << _strPathPlayerActions;
		__debugbreak();
	}
	file2.close();

	//player item strings
	ifstream file3(_strPathPlayerItems);
	if (file3.is_open()) {
		string tempStr = "";
		while (getline(file3, tempStr))
		{
			m_vecStrPlayerItems.emplace_back(tempStr);
		}
	}
	else {
		cerr << "FAILED TO OPEN FILE LOCATED AT: " << _strPathPlayerItems;
		__debugbreak();
	}
	file3.close();
}
