#pragma once

#ifndef LIB_BACKENDLOADERINCLUDE_HPP
#define LIB_BACKENDLOADERINCLUDE_HPP

#include <lib/include/types/str.hpp>
#include "interfaces.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

namespace lib
{
	namespace backend
	{
		class BackendLoader
		{
		public:
			BackendLoader();
			~BackendLoader();

			bool load(const str&filename);
			void* loadFunc(const str&fname);
		private:
			HINSTANCE instance;
			
		};

		class LoadedFunction
		{

		};
	}
}

#endif
