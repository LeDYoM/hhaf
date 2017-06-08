#include "backendloader.hpp"

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

		void* BackendLoader::loadFunc(const str&fname)
		{
			void* funci = GetProcAddress(instance, fname.c_str());
			if (!funci) {
				return nullptr;
			}

			return funci;
		}

		bool BackendLoader::load(const str & filename)
		{
			instance = LoadLibrary(filename.c_str());

			if (instance) {
				return true;
			}
			return false;

		}
	}
}
