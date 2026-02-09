#pragma once
#ifndef __BATTLELEVEL_H__
#define __BATTLELEVEL_H__

#include "Level/Level.h"
#include "EngineCommon/RTTI.h"
#include "ClientCommon/Client_Enum.h"

USING(System)
class BattleLevel : public Level
{
	RTTI_DECLARATIONS(BattleLevel, Level)
public:
	BattleLevel(const string _strPath);
	virtual ~BattleLevel();
public:
	// Inherited via Level
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;
public:
	void Update_PlayerStatus();
	void Update_NoticeSituation();
	void PlayerAction();
	void EnemyHit();
	void Intermission();
	void EnemyAction();
	void PlayerHit();
public:
	inline void SetBattleSequence(const E_BATTLESEQUENCE& _eSeq) { m_eBattleSeq = _eSeq; }
public:
	void LoadBattleLevelTemplate(const string _strPath);
private:
	vector<string> m_vecBattleScene;

private:
	static float s_fTimeDelay;
	float m_fTimeAcc = 0.f;
private:
private:
	bool m_bIsNextSeqReady = false;
private:
	string m_strPlayerHP = "";
	string m_strPlayerMP = "";
	string m_strEnemyHP = "";
	string m_strNotiSituation = "";
private:
	Vector2 m_vPosPlayerHP = Vector2::Zero;
	Vector2 m_vPosPlayerMP = Vector2::Zero;
	Vector2 m_vPosEnemyHP = Vector2::Zero;
	Vector2 m_vPosNotiSituation = Vector2::Zero;
private:
	E_BATTLESEQUENCE m_eBattleSeq = E_BATTLESEQUENCE::E_BATTLESEQUENCE_NONE;
};


#endif // !__BATTLELEVEL_H__