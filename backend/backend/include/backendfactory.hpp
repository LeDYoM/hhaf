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
        BackendFactory();
        ~BackendFactory();

        IWindowProviderInfo* getWindowProviderInfo();
        IWindow* getOrCreateWindow();
        ITextureFactory* getTextureFactory();
        ITTFontFactory* getTTFontFactory();
        IShaderFactory* getShaderFactory();
        inline ITextureFactory &textureFactory() { return *getTextureFactory(); }
        inline ITTFontFactory &ttfontFactory() { return *getTTFontFactory(); }
        inline IShaderFactory &shaderFactory() { return *getShaderFactory(); }

    private:
        uptr<BackendRegister> backend_register_;
        IWindowProviderInfo* m_windowProviderInfo;
        IWindow* m_window;
        ITextureFactory* m_textureFactory;
        ITTFontFactory* m_ttfontFactory;
        IShaderFactory* m_shaderFactory;
    };
}

#endif
