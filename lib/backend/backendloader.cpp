#include "backendloader.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

namespace lib
{
	namespace backend
	{
		BackendLoader::BackendLoader()
		{
		}

		BackendLoader::~BackendLoader()
		{
		}

		void * BackendLoader::loadFunc(const str&fname)
		{
			void *funci = GetProcAddress((HINSTANCE)instance, fname.c_str());
			if (!funci) {
				return nullptr;
			}

			return funci;
		}

		bool BackendLoader::load(const str & filename)
		{
			void* hGetProcIDDLL = LoadLibrary(filename.c_str());

			if (!hGetProcIDDLL) {
				return false;
			}

		}
	}
}
