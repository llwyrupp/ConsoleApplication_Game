#pragma once
#ifndef __ENGINE_ENUM_H__
#define __ENGINE_ENUM_H__

enum class ENGINE_DLL Color : unsigned short {
	eBlack = 0,
	eBlue = FOREGROUND_BLUE,
	eGreen = FOREGROUND_GREEN,
	eRed = FOREGROUND_RED,
	eWhite = eBlue | eGreen | eRed,
};

#endif//!__ENGINE_ENUM_H__