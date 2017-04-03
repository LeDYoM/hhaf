#include "backendfactory.hpp"
#include "sfml/renderwindow.hpp"

namespace lib
{
	namespace backend
	{
		uptr<IWindow> lib::backend::BackendFactory::getOrCreateWindow()
		{
			return muptr<RenderWindow>();
		}
	}
}
