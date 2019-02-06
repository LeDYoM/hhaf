#include "backendfactory.hpp"

#include <lib/include/core/log.hpp>

#include <lib/include/backend/interfaces.hpp>
#include <loader/include/loader.hpp>

namespace lib::backend
{
	BackendFactory *BackendFactory::m_instance = nullptr;

	BackendFactory::BackendFactory()
	{
		using namespace loader;
		auto *loader(createLoader());
		IWindowProviderInfo * wpitemp{ nullptr };
		IWindow * wtemp{ nullptr };
		ITTFontFactory *ttfftemp{ nullptr };
		ITextureFactory *tftemp{ nullptr };
        IShaderFactory *sftemp{ nullptr };

		static const char *sh_name = "bsfml";
		if (loader->loadModule(sh_name)) 
        {

			auto fp_createWindowProviderInfo = (p_createWindowProviderInfo)loader->loadMethod(sh_name, "createWindowProviderInfo");
            auto fp_destroyWindowProviderInfo = (p_destroyWindowProviderInfo)loader->loadMethod(sh_name, "destroyWindowProviderInfo");

            if (fp_createWindowProviderInfo && fp_destroyWindowProviderInfo)
            {
                wpitemp = (*fp_createWindowProviderInfo)();
                m_windowProviderInfo = sptr<IWindowProviderInfo>(wpitemp, *fp_destroyWindowProviderInfo);
            }

            auto fp_createWindow = (p_createWindow)loader->loadMethod(sh_name, "createWindow");
            auto fp_destroyWindow = (p_destroyWindow)loader->loadMethod(sh_name, "destroyWindow");

            if (fp_createWindow && fp_destroyWindow)
            {
                wtemp = (*fp_createWindow)();
                m_window = sptr<IWindow>(wtemp, *fp_destroyWindow);
            }

            auto fp_createTTFontFactory = (p_createTTFontFactory)loader->loadMethod(sh_name, "createTTFontFactory");
            auto fp_destroyTTFontFactory = (p_destroyTTFontFactory)loader->loadMethod(sh_name, "destroyTTFontFactory");

            if (fp_createTTFontFactory && fp_destroyTTFontFactory)
            {
                ttfftemp = (*fp_createTTFontFactory)();
                m_ttfontFactory = sptr<ITTFontFactory>(ttfftemp, *fp_destroyTTFontFactory);
            }

            auto fp_createTextureFactory = (p_createTextureFactory)loader->loadMethod(sh_name, "createTextureFactory");
            auto fp_destroyTextureFactory = (p_destroyTextureFactory)loader->loadMethod(sh_name, "destroyTextureFactory");

            if (fp_createTextureFactory && fp_destroyTextureFactory)
            {
                tftemp = (*fp_createTextureFactory)();
                m_textureFactory = sptr<ITextureFactory>(tftemp, *fp_destroyTextureFactory);
            }

            auto fp_createShaderFactory = (p_createShaderFactory)loader->loadMethod(sh_name, "createShaderFactory");
            auto fp_destroyShaderFactory = (p_destroyShaderFactory)loader->loadMethod(sh_name, "destroyShaderFactory");

			if (fp_createShaderFactory && fp_destroyShaderFactory)
            {
                sftemp = (*fp_createShaderFactory)();
                m_shaderFactory = sptr<IShaderFactory>(sftemp, *fp_destroyShaderFactory);
			}
        }
        else 
        {
            // Cannot load shared library dynamically.
            log_release_error("Fatal: Cannot load shared library ", sh_name);
        }

	}

	BackendFactory::~BackendFactory() 
	{
		// Not necessary, but make sure the pointers are deleted before the destructor finishes
		m_windowProviderInfo = nullptr;
		m_window = nullptr;
		m_textureFactory = nullptr;
		m_ttfontFactory = nullptr;
        m_shaderFactory = nullptr;

		loader::destroyLoader();
	}

	bool BackendFactory::initilialize(const str&)
	{
		if (!m_instance) {
			m_instance = new BackendFactory;
			log_release_info("Using backend: ", m_instance->m_windowProviderInfo->info());
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

    sptr<IShaderFactory> BackendFactory::getShaderFactory()
    {
        return m_shaderFactory;
    }
}
