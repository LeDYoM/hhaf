#include "backendfactory.hpp"
#include "backendregister.hpp"

#include <lib/include/core/log.hpp>

#include <backend_dev/include/interfaces.hpp>
#include <loader/include/loader.hpp>

namespace lib::backend
{
	template <typename FactoryType>
	inline bool fillFactory(const uptr<BackendRegister>& backend_register,FactoryType** factory_to_fill)
	{
		if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>()); factory)
		{
			(*factory_to_fill) = factory->create();
			return (*factory_to_fill) != nullptr;
		}
		return false;
	}

	template <typename FactoryType>
	inline bool emptyFactory(const uptr<BackendRegister>& backend_register, FactoryType** factory_to_empty)
	{
		if (auto factory(backend_register->getFactory<IFactoryOf<FactoryType>>()); factory)
		{
			if (factory_to_empty && *factory_to_empty)
			{
				factory->destroy(*factory_to_empty);
				(*factory_to_empty) = nullptr;
				return true;
			}
		}
		return false;
	}

	BackendFactory *BackendFactory::m_instance = nullptr;

	BackendFactory::BackendFactory()
	{
		using namespace loader;
		auto *loader(createLoader());

		static const char *sh_name = "bsfml";
		if (loader->loadModule(sh_name)) 
        {
			auto fp_init_lib = (p_initLib)loader->loadMethod(sh_name, "init_lib");
			auto fp_finish_lib = (p_initLib)loader->loadMethod(sh_name, "finish_lib");

			if (fp_init_lib && fp_finish_lib)
			{
				backend_register_ = muptr<BackendRegister>();
				backend_register_->setLibFuncs(fp_init_lib, fp_finish_lib);
				backend_register_->init();
			}

			bool result{ fillFactory(backend_register_, &m_windowProviderInfo) };
			result &= fillFactory(backend_register_, &m_window);
			result &= fillFactory(backend_register_, &m_ttfontFactory);
			result &= fillFactory(backend_register_, &m_textureFactory);
			result &= fillFactory(backend_register_, &m_shaderFactory);
			assert_debug(result, "Not all factories created");
        }
        else 
        {
            // Cannot load shared library dynamically.
            log_release_error("Fatal: Cannot load shared library ", sh_name);
        }
	}

	BackendFactory::~BackendFactory() 
	{
		bool result{ emptyFactory(backend_register_, &m_windowProviderInfo) };
		result &= emptyFactory(backend_register_, &m_window);
		result &= emptyFactory(backend_register_, &m_textureFactory);
		result &= emptyFactory(backend_register_, &m_ttfontFactory);
		result &= emptyFactory(backend_register_, &m_shaderFactory);
		backend_register_->finish();

		backend_register_.reset();

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

	IWindowProviderInfo* BackendFactory::getWindowProviderInfo()
	{
		return m_windowProviderInfo;
	}

	IWindow* lib::backend::BackendFactory::getOrCreateWindow()
	{
		return m_window;
	}

	ITextureFactory* BackendFactory::getTextureFactory()
	{
		return m_textureFactory;
	}

	ITTFontFactory* BackendFactory::getTTFontFactory()
	{
		return m_ttfontFactory;
	}

    IShaderFactory* BackendFactory::getShaderFactory()
    {
        return m_shaderFactory;
    }
}
