#include "backendfactory.hpp"
#include "sfml/renderwindow.hpp"
#include <lib/core/log.hpp>

namespace lib
{
	namespace backend
	{
		BackendFactory *BackendFactory::m_instance = nullptr;

		BackendFactory::BackendFactory() {}
		BackendFactory::~BackendFactory() {}

		bool BackendFactory::initilialize()
		{
			if (!m_instance) {
				m_instance = new BackendFactory;
				return true;
			}

			return false;
		}

		bool BackendFactory::destroy()
		{
			if (m_instance) {
				delete m_instance;
				m_instance = nullptr;
				return true;
			}
			return false;
		}

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
