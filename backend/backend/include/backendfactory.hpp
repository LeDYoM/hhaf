#pragma once

#ifndef LIB_BACKEND_FACTORY_HPP
#define LIB_BACKEND_FACTORY_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iresourcefactories.hpp>

#include "backendregister.hpp"

namespace lib::backend
{
    class BackendFactory final
    {
    public:
        BackendFactory();
        ~BackendFactory();

        IWindow* getOrCreateWindow();
        IWindowProviderInfo* getWindowProviderInfo() const noexcept;
        ITextureFactory* getTextureFactory() const noexcept;
        ITTFontFactory* getTTFontFactory() const noexcept;
        IShaderFactory* getShaderFactory() const noexcept;
        IBMPFontFactory* getBMPFontFactory() const noexcept;
        inline IWindowProviderInfo &windowProviderInfo() const { return *getWindowProviderInfo(); }
        inline ITextureFactory &textureFactory() const { return *getTextureFactory(); }
        inline ITTFontFactory &ttfontFactory() const { return *getTTFontFactory(); }
        inline IShaderFactory &shaderFactory() const { return *getShaderFactory(); }
        inline IBMPFontFactory &bmpFontFactory() const { return *getBMPFontFactory(); }

    private:
        uptr<BackendRegister> backend_register_;
        IWindowProviderInfo* m_windowProviderInfo{nullptr};
        IWindow* m_window{nullptr};
        ITextureFactory* m_textureFactory{nullptr};
        ITTFontFactory* m_ttfontFactory{nullptr};
        IShaderFactory* m_shaderFactory{nullptr};
        IBMPFontFactory *m_bmpFontFactory{nullptr};
    };
}

#endif
