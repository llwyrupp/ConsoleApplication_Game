#include "EngineCommon/Engine_Includes.h"
#include "Singleton/Singleton.h"

BEGIN(System)

template<typename T>
T* Singleton::m_pInstance = nullptr;

END