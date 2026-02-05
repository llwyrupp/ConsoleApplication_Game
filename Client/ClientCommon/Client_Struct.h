#pragma once
#ifndef __CLIENT_STRUCT_H__
#define __CLIENT_STRUCT_H__

typedef struct tagPlayerInfo {
	int iHP;
	int iMP;

}PLAYERINFO;

typedef struct tagEnemyInfo {
	;//적군타입
	int iHP;
	int iMP;
}ENEMYINFO;

typedef struct tagItemInfo {
	char* pName;//아이템이름
	char* pDesc;//아이템설명
}ITEMINFO;

typedef struct tagMeleeInfo {
	char* pName;//무기이름
	char* pDesc;//무기설명
}MELEEINFO;

typedef struct tagGearInfo {
	char* pName;//장비이름
	char* pDesc;//장비설명
}GEARINFO;

typedef struct tagSkillInfo {
	char* pName;//스킬이름
	char* pDesc;//스킬설명
};

#endif//!__CLIENT_STRUCT_H__