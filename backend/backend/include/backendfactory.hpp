#ifndef HAF_BACKEND_FACTORY_HPP
#define HAF_BACKEND_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <backend_dev/include/iresourcefactories.hpp>

namespace agloader
{
    class Loader;
}

namespace haf::backend
{
class BackendRegister;
class IWindow;
class IRenderTarget;

/**
 * @brief Class representing a factory for backend classes.
 * This class initializes and stores subsystems of a backend.
 */
class BackendFactory final
{
public:
    BackendFactory();
    ~BackendFactory();

    htps::rptr<IWindow> getWindow() const noexcept;
    htps::rptr<IRenderTarget> getRenderTarget() const noexcept;
    htps::rptr<ITextureFactory> getTextureFactory() const noexcept;
    htps::rptr<ITTFontFactory> getTTFontFactory() const noexcept;
    htps::rptr<IShaderFactory> getShaderFactory() const noexcept;
    htps::rptr<IBMPFontFactory> getBMPFontFactory() const noexcept;
    ITextureFactory& textureFactory() const;
    ITTFontFactory& ttfontFactory() const;
    IShaderFactory& shaderFactory() const;
    IBMPFontFactory& bmpFontFactory() const;

private:
    htps::uptr<BackendRegister> backend_register_;
    htps::rptr<IWindow> window_{nullptr};
    htps::rptr<IRenderTarget> render_target_{nullptr};
    htps::rptr<ITextureFactory> textureFactory_{nullptr};
    htps::rptr<ITTFontFactory> ttfontFactory_{nullptr};
    htps::rptr<IShaderFactory> shaderFactory_{nullptr};
    htps::rptr<IBMPFontFactory> bmpFontFactory_{nullptr};
    htps::rptr<agloader::Loader> loader_{nullptr};
};
}  // namespace haf::backend

#endif
