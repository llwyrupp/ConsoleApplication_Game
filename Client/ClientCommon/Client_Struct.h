#pragma once
#ifndef __CLIENT_STRUCT_H__
#define __CLIENT_STRUCT_H__

typedef struct tagPlayerInfo {
	int iHP = 0;
	int iMP = 0;
	int iAttack = 0;
	int iDefense = 0;
	int iCritRate = 0;
	int iCritDmg = 0;
}PLAYERINFO;

typedef struct tagEnemyInfo {
	tagEnemyInfo() {}
	tagEnemyInfo(const char* _pName, int _iHP, int _iAtk, int _iDef) 
		:iHP(_iHP), iAttack(_iAtk), iDefense(_iDef)
	{
		//pName = new char[MAX_STRING_LEN] + 1;//always include +1 for null.
		//size_t szLen = strlen(_pName);
		//strcpy_s(pName, sizeof(pName) * szLen, _pName);
	}
	~tagEnemyInfo() {
		//Safe_Delete_Arr(pName);
		/*if (pName)
		{
			delete[] pName;
			pName = nullptr;
		}*/
	}

	char* pName = nullptr;
	int iHP = 0;
	int iAttack = 0;
	int iDefense = 0;
}ENEMYINFO;

typedef struct tagItemInfo {
	char* pName = nullptr;
	char* pDesc = nullptr;
}ITEMINFO;

typedef struct tagMeleeInfo {
	char* pName = nullptr;
	char* pDesc = nullptr;
}MELEEINFO;

typedef struct tagGearInfo {
	char* pName = nullptr;
	char* pDesc = nullptr;
	int iAttack = 0;
	int iDefense = 0;
}GEARINFO;

typedef struct tagSkillInfo {
	char* pName;//
	char* pDesc;//
}SKILLINFO;

#endif//!__CLIENT_STRUCT_H__