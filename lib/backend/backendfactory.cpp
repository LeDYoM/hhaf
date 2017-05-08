#include "backendfactory.hpp"
#include <lib/core/log.hpp>

#include "sfml/renderwindow.hpp"
#include "sfml/texturefactory.hpp"
#include "sfml/ttfontfactory.hpp"

namespace lib
{
	namespace backend
	{
		BackendFactory *BackendFactory::m_instance = nullptr;

		BackendFactory::BackendFactory()
		{
			logConstruct_NOPARAMS;
			m_windowProviderInfo = msptr<sfmlb::WindowBackendInfo>();
			m_window = msptr<sfmlb::RenderWindow>();
			m_textureFactory = msptr<sfmlb::TextureFactory>();
			m_ttfontFactory = msptr<sfmlb::TTFontFactory>();
		}
		BackendFactory::~BackendFactory() 
		{
			logDestruct_NOPARAMS;
		}

		bool BackendFactory::initilialize()
		{
			if (!m_instance) {
				m_instance = new BackendFactory;
				logInfo("Using backend: ");
				logInfo(m_instance->m_windowProviderInfo->info());
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

		sptr<IWindowProviderInfo> BackendFactory::getWindowProviderInfo()
		{
			return m_windowProviderInfo;
		}
		sptr<IWindow> lib::backend::BackendFactory::getOrCreateWindow()
		{
			return m_window;
		}
		sptr<ITextureFactory> BackendFactory::getTextureFactory()
		{
			return m_textureFactory;
		}

		sptr<ITTFontFactory> BackendFactory::getTTFontFactory()
		{
			return m_ttfontFactory;
		}
	}
}
