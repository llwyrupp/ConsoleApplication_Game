#pragma once
#ifndef __BATTLELEVEL_H__
#define __BATTLELEVEL_H__

#include "ClientCommon/Client_Defines.h"
#include "ClientCommon/Client_Enum.h"
#include "Level/Level.h"
#include "EngineCommon/RTTI.h"
#include "Math/Vector2.h"

using namespace System; 
class Enemy;
class BattlePlayer;
class BattleLevel : public Level
{
	RTTI_DECLARATIONS(BattleLevel, Level)
public:
	BattleLevel(const string _strPathBattleScene, const string _strPathPlayerActions, const string _strPathPlayerItems);
	virtual ~BattleLevel();
public:
	// Inherited via Level
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
public://things that need to be updated every frame
	void Update_PlayerStatus();
	void Update_EnemyStatus();
	void Update_Arrow();
public://battle sequences(auto-updated)
	void PlayerAction();
	void EnemyHit();
	void Intermission();
	void EnemyAction();
	void PlayerHit();
public://player's actions(user-updated)
	void PlayerAttack();
	void PlayerGuard();
	void PlayerOpenInven();
	void PlayerUseItem();
	void PlayerTryRun();
public:
	inline const E_BATTLESEQUENCE& GetBattleSequence() const { return m_eBattleSeq; }
	inline void SetBattleSequence(const E_BATTLESEQUENCE& _eSeq) { m_eBattleSeq = _eSeq; }
	inline const E_PLAYERACTION& GetPlayerAction() const { return m_ePlayerAction; }
	inline void SetPlayerAction(const E_PLAYERACTION& _eAction) { m_ePlayerAction = _eAction; }
	inline const int& GetCurInvenIdx() const { return m_iCurInventoryIndex; }
	inline void SetCurInvenIdx(int _iIdx) { m_iCurInventoryIndex = _iIdx; }
	inline const int& GetCurActionChoiceArrowIdx() const { return m_iCurActionChoiceArrowIdx; }
	inline void SetCurActionChoiceArrowIdx(int _iIdx) { m_iCurActionChoiceArrowIdx = _iIdx; }
	
public:
	void LoadBattleLevelTemplate(const string _strPathBattleScene, const string _strPathPlayerActions, const string _strPathPlayerItems);
private:
	vector<string> m_vecStrBattleScene;
	vector<string> m_vecStrPlayerActions;
	vector<string> m_vecStrPlayerItems;
private:
	static float s_fSequenceTimeDelay;
	float m_fTimeAcc = 0.f;

private:
	int m_iCurInventoryIndex = 0;
	int m_iCurActionChoiceArrowIdx = 0;
private:
	
	bool m_bEnemyHPFlash = false;
	bool m_bHPFlash = false;
	bool m_bIsBattleOver = false;
	bool m_bIsNextSeqReady = true;
private://what to be seen on the screen
	string m_strPlayerHP = "";
	string m_strPlayerMP = "";
	string m_strEnemyHP = "";
	string m_strNotiSituation = "";
	string m_strDesc = "";
	const string m_strActionChoiceArrow = ">";
	const string m_strInvenArrow = ">";
private://where to be seen on the screen.
	Vector2 m_vPosPlayerHP = Vector2::Zero;
	Vector2 m_vPosPlayerMP = Vector2::Zero;
	Vector2 m_vPosEnemyHP = Vector2::Zero;
	Vector2 m_vPosNotiSituation = Vector2::Zero;
	Vector2 m_vPosDesc = Vector2::Zero;

	//TODO: add inven pos choice.
	Vector2 m_vPosChoice[MAX_PLAYERINVEN_SIZE] = {};
private:
	Vector2 m_vPosActionChoiceArrow[MAX_PLAYERINVEN_SIZE] = {};
	Vector2 m_vPosInvenArrow[MAX_PLAYERINVEN_SIZE] = {};
private:
	E_BATTLESEQUENCE m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_WAITFORINPUT;
	E_PLAYERACTION m_ePlayerAction = E_PLAYERACTION::E_PLAYERACTION_NONE;
	E_ENEMYSTATE m_eEnemyState = E_ENEMYSTATE::E_ENEMYSTATE_NONE;

private:
	unsigned short m_sColor_PlayerHP = 2;
	unsigned short m_sColor_EnemyHP = 4;
private:
	Enemy* m_pEnemy = nullptr;
};


#endif // !__BATTLELEVEL_H__