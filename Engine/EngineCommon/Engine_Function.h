#pragma once

#ifndef __ENGINE_FUNCTION_H__
#define __ENGINE_FUNCTION_H__

#pragma region GENERAL
//check if the pointer is a nullptr. if it is, return.
template<typename T>
void CheckIfNullReturn(T*& ptr) {
	if (ptr == nullptr)
		return;
}
#pragma endregion GENERAL

#pragma region MEMORY
template<typename T>
void Safe_Delete(T*& ptr) {
	if (ptr) {
		delete ptr;
		ptr = nullptr;
	}
}

template<typename T>
void Safe_Delete_Arr(T*& ptr) {
	if (ptr) {
		delete[] ptr;
		ptr = nullptr;
	}
}
#pragma endregion MEMORY

#pragma region RANDOM

BEGIN(Util)
inline void SetRandomSeed() {
	//시간값을 랜덤 종자값으로 설정
	srand(static_cast<unsigned int>(time(nullptr)));
}

//정수 난수 함수
inline int RandomInt(int iMin, int iMax) {
	int iDiff = iMax - iMin + 1;
	// div by 32768
	return ((iDiff * rand()) / (RAND_MAX + 1)) + iMin;
}

inline float RandomRange(float fMin, float fMax) {
	//0~1 사이 랜덤 float값
	float fRandom = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float fDiff = fMax - fMin;
	return (fRandom * fDiff) + fMin;
}
END
#pragma endregion RANDOM

#endif //__ENGINE_FUNCTION_H__