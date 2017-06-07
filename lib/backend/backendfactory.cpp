#include "backendfactory.hpp"
#include "backendloader.hpp"
#include <lib/core/log.hpp>

#include "interfaces.hpp"

namespace lib
{
	namespace backend
	{
		BackendFactory *BackendFactory::m_instance = nullptr;

		BackendFactory::BackendFactory()
		{
			logConstruct_NOPARAMS;
			lib::backend::IWindowProviderInfo * wpitemp{ nullptr };
			lib::backend::IWindow * wtemp{ nullptr };
			lib::backend::ITTFontFactory *ttfftemp{ nullptr };
			lib::backend::ITextureFactory *tftemp{ nullptr };
			BackendLoader bloader;
			if (bloader.load("bsfml")) {
				auto fp_createWindowProviderInfo = (p_createWindowProviderInfo)bloader.loadFunc("createWindowProviderInfo");
				auto fp_createWindow = (p_createWindow)bloader.loadFunc("createWindow");
				auto fp_createTTFontFactory = (p_createTTFontFactory)bloader.loadFunc("createTTFontFactory");
				auto fp_createTextureFactory = (p_createTextureFactory)bloader.loadFunc("createTextureFactory");
				if (fp_createWindowProviderInfo && fp_createWindow && fp_createTTFontFactory && fp_createTextureFactory) {
					wpitemp = (*fp_createWindowProviderInfo)();
					wtemp = (*fp_createWindow)();
					ttfftemp = (*fp_createTTFontFactory)();
					tftemp = (*fp_createTextureFactory)();
				}
			}
			m_windowProviderInfo = sptr<IWindowProviderInfo>(wpitemp);
			m_window = sptr<IWindow>(wtemp);
			m_textureFactory = sptr<ITextureFactory>(tftemp);
			m_ttfontFactory = sptr<ITTFontFactory>(ttfftemp);
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

		bool BackendFactory::initilialize(const str&file)
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
