#pragma once

#ifndef LIB_BACKENDLOADERINCLUDE_HPP
#define LIB_BACKENDLOADERINCLUDE_HPP

#include <lib/include/types/str.hpp>
#include "interfaces.hpp"

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
			void *loadFunc(const str&fname);
		private:
			void *instance;
			
		};

		class LoadedFunction
		{

		};
	}
}

#endif
