#pragma once

#ifndef LIB_BACKEND_FACTORY_HPP
#define LIB_BACKEND_FACTORY_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/interfaces.hpp>

#include "backendregister.hpp"

namespace lib::backend
{
	class BackendFactory final
	{
	public:
		static bool initilialize(const str&file);
		static bool destroy();
		IWindowProviderInfo* getWindowProviderInfo();
		IWindow* getOrCreateWindow();
		ITextureFactory* getTextureFactory();
		ITTFontFactory* getTTFontFactory();
        IShaderFactory* getShaderFactory();
		static inline BackendFactory *const instance() noexcept { return m_instance; }
	private:
		BackendFactory();
		~BackendFactory();
		uptr<BackendRegister> backend_register_;
		IWindowProviderInfo* m_windowProviderInfo;
		IWindow* m_window;
		ITextureFactory* m_textureFactory;
		ITTFontFactory* m_ttfontFactory;
        IShaderFactory* m_shaderFactory;
		static BackendFactory *m_instance;
	};

	static inline BackendFactory &backendFactory() { return *(BackendFactory::instance()); }
	static inline ITextureFactory &textureFactory() { return *(BackendFactory::instance()->getTextureFactory()); }
	static inline ITTFontFactory &ttfontFactory() { return *(BackendFactory::instance()->getTTFontFactory()); }
    static inline IShaderFactory &shaderFactory() { return *(BackendFactory::instance()->getShaderFactory()); }
}

#endif
