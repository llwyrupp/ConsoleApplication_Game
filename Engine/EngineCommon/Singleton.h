#pragma once
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include "EngineCommon/Engine_Includes.h"

	template<typename T>
	class Singleton {
	protected:
		//only derived class can call
		Singleton() = default;
		~Singleton() = default;

	protected:
		//prevent copying and assignment. (cloning)
		Singleton(const Singleton&) = delete;//no copy constructor allowed.
		Singleton& operator=(const Singleton&) = delete;//no assignment allowed.

	public:
		inline static T& Get_Instance() {
			//"Lazy Initialization," and it guarantees your objects exist exactly when you need them.
			//created ONCE ONLY
			static T* instance;
			return *instance;

			/*
			Benefit: No separate .cpp definition needed.
			Benefit: Thread-safe by default (since C++11).
			Benefit: No manual new or delete required. Memory is managed automatically by the program's data segment.
			*/
		}
	};

#endif//!__SINGLETON_H__