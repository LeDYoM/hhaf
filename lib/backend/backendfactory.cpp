#include "backendfactory.hpp"
#include "sfml/renderwindow.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace backend
	{
		uptr<IWindowProviderInfo> BackendFactory::getWindowProviderInfo()
		{
			return muptr<WindowBackendInfo>();
		}
		uptr<IWindow> lib::backend::BackendFactory::getOrCreateWindow()
		{
			return muptr<RenderWindow>();
		}
	}
}
