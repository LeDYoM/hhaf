#ifndef LIB_BACKEND_FACTORY_HPP
#define LIB_BACKEND_FACTORY_HPP

#include "iwindow.hpp"

namespace lib
{
	namespace backend
	{
		class BackendFactory
		{
		public:
			uptr<IWindow> getOrCreateWindow();
		};
	}
}
#endif

