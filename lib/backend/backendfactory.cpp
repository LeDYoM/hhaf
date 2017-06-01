#include "backendfactory.hpp"
#include <lib/core/log.hpp>

#include "sfml/renderwindow.hpp"
#include "sfml/texturefactory.hpp"
#include "sfml/ttfontfactory.hpp"
#include "interfaces.hpp"

namespace lib
{
	namespace backend
	{
		BackendFactory *BackendFactory::m_instance = nullptr;

		BackendFactory::BackendFactory()
		{
			logConstruct_NOPARAMS;
			m_windowProviderInfo = msptr<sfmlb::WindowBackendInfo>();
			m_window = sptr<IWindow>(new sfmlb::RenderWindow);
			m_textureFactory = sptr<ITextureFactory>(new sfmlb::TextureFactory);
//			m_ttfontFactory = sptr<ITTFontFactory>(new sfmlb::TTFontFactory);
			m_ttfontFactory = sptr<ITTFontFactory>(createTTFontFactory());
		}
		BackendFactory::~BackendFactory() 
		{
			// Not necessary, but make sure the pointers are deleted before the descructor finishes
			m_windowProviderInfo = nullptr;
			m_window = nullptr;
			m_textureFactory = nullptr;
			m_ttfontFactory = nullptr;

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
