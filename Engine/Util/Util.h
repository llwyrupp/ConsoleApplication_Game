#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__


#include "Math/Vector2.h"

USING(System)

BEGIN(Util)
// 콘솔 커서 위치 이동(설정)하는 함수.
inline void SetConsolePos(const Vector2& vPos) { 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),static_cast<COORD>(vPos));
}
// 콘솔 텍스트 설정 함수.
inline void SetConsoleTextColor(Color color) { 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<unsigned short>(color)); 
}

// 커서 끄기.
inline void TurnOffCursor(){ 
	CONSOLE_CURSOR_INFO info = {};	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}

// 커서 켜기.
inline void TurnOnCursor()
{
	// 커서 끄기.
	CONSOLE_CURSOR_INFO info = {};
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);

	info.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
}
END

#endif//!__UTIL_H__