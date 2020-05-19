#pragma once

#ifndef HAF_BACKEND_FACTORY_HPP
#define HAF_BACKEND_FACTORY_HPP

#include <mtypes/include/types.hpp>
#include <backend_dev/include/iresourcefactories.hpp>

namespace haf::backend
{
class BackendRegister;
class IWindow;

/**
 * @brief Class representing a factory for backend classes.
 * This class initializes and stores subsystems of a backend.
 */
class BackendFactory final
{
public:
    BackendFactory();
    ~BackendFactory();

    mtps::rptr<IWindow> getWindow();
    mtps::rptr<ITextureFactory> getTextureFactory() const noexcept;
    mtps::rptr<ITTFontFactory> getTTFontFactory() const noexcept;
    mtps::rptr<IShaderFactory> getShaderFactory() const noexcept;
    mtps::rptr<IBMPFontFactory> getBMPFontFactory() const noexcept;
    ITextureFactory &textureFactory() const;
    ITTFontFactory &ttfontFactory() const;
    IShaderFactory &shaderFactory() const;
    IBMPFontFactory &bmpFontFactory() const;

private:
    mtps::uptr<BackendRegister> backend_register_;
    mtps::rptr<IWindow> window_{nullptr};
    mtps::rptr<ITextureFactory> textureFactory_{nullptr};
    mtps::rptr<ITTFontFactory> ttfontFactory_{nullptr};
    mtps::rptr<IShaderFactory> shaderFactory_{nullptr};
    mtps::rptr<IBMPFontFactory> bmpFontFactory_{nullptr};
};
} // namespace haf::backend

#endif
