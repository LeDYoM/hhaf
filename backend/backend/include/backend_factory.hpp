#ifndef HAF_BACKEND_FACTORY_HPP
#define HAF_BACKEND_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
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

    /**
     * @brief Load a new shared object containing factories to be used by haf
     *
     * @param file_name File name containing the backend factories library to
     * load
     * @return true Successfully load
     * @return false Failed in loading
     */
    bool loadBackendFile(htps::str const& file_name);

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
    using BackendRegisterUptr   = htps::uptr<BackendRegister>;
    using BackendRegisteredData = htps::pair<htps::str, BackendRegisterUptr>;
    htps::vector<BackendRegisteredData>
        loaded_modules_;  //< List of loaded backend libraries.
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
