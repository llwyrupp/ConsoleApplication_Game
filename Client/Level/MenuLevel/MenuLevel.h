#pragma once
#ifndef __MENULEVEL_H__
#define __MENULEVEL_H__

#include "EngineCommon/Engine_Defines.h"
#include "EngineCommon/Engine_Function.h"
#include "EngineCommon/Engine_Enum.h"
#include "EngineCommon/RTTI.h"
#include "Level/Level.h"

using namespace System;
typedef struct tagMenuObject {
	//메뉴가 실행됐을때 실행될 함수의 타입(콜백으로 실행됨)
	//void* 형을 반환하는 함수를 사용
	using OnSelected = void(*)();

	tagMenuObject(const char* _pText, OnSelected _onSel)
		:fcOnSelected(_onSel)
	{
		size_t szLen = strlen(_pText) + 1;
		pText = new char[szLen];
		strcpy_s(pText, sizeof(char) * szLen, _pText);
	}
	~tagMenuObject() {
		Safe_Delete_Arr(pText);
	}

	char* pText = nullptr;
	OnSelected fcOnSelected = nullptr;
}MENUOBJECT;

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)
public:
	MenuLevel();
	virtual ~MenuLevel();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Render() override;

private:
	int m_iCurMenuIdx = 0;
	//메뉴에 띄울 옵션들을 구조체로 관리한다
	//1.게임시작
	//2.게임종료
	//3.설정(?)
	vector<MENUOBJECT*> m_vecMenuObjects;

	Color m_eSelectedColor = Color::eGreen;
	Color m_eUnselectedColor = Color::eWhite;

};

#endif
