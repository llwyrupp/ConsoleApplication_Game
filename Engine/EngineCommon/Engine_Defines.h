#pragma once
#ifndef __ENGINE_DEFINES_H__
#define __ENGINE_DEFINES_H__
#pragma warning(disable: 4251)	// 미봉책(방법 없음).
#pragma warning(disable: 4172)	// 위험성 인지한 상태로 사용.

#define MAX_BUFFER_LEN 2048
#define MAX_HEADER_LEN 24

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include<crtdbg.h>
#endif //_DEBUG

#endif//!__ENGINE_DEFINES_H__