#pragma once

#ifndef HAF_BACKEND_FACTORY_HPP
#define HAF_BACKEND_FACTORY_HPP

#include <backend_dev/include/iresourcefactories.hpp>

namespace haf::backend
{
class BackendRegister;
class IWindow;
class IWindowProviderInfo;

/**
 * @brief Class representing a factory for backend classes.
 * This class initializes and stores subsystems of a backend.
 */
class BackendFactory final
{
public:
    BackendFactory();
    ~BackendFactory();

    IWindow *getWindow();
    IWindowProviderInfo *getWindowProviderInfo() const noexcept;
    ITextureFactory *getTextureFactory() const noexcept;
    ITTFontFactory *getTTFontFactory() const noexcept;
    IShaderFactory *getShaderFactory() const noexcept;
    IBMPFontFactory *getBMPFontFactory() const noexcept;
    IWindowProviderInfo &windowProviderInfo() const;
    ITextureFactory &textureFactory() const;
    ITTFontFactory &ttfontFactory() const;
    IShaderFactory &shaderFactory() const;
    IBMPFontFactory &bmpFontFactory() const;

private:
    mtps::uptr<BackendRegister> backend_register_;
    IWindowProviderInfo *m_windowProviderInfo{nullptr};
    IWindow *m_window{nullptr};
    ITextureFactory *m_textureFactory{nullptr};
    ITTFontFactory *m_ttfontFactory{nullptr};
    IShaderFactory *m_shaderFactory{nullptr};
    IBMPFontFactory *m_bmpFontFactory{nullptr};
};
} // namespace haf::backend

#endif
