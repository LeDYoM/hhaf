#ifndef HAF_BACKEND_FACTORY_HPP
#define HAF_BACKEND_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <backend_dev/include/iresourcefactories.hpp>

namespace agl
{
class Loader;
}

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
    htps::rptr<ITextureFactory> getTextureFactory() const noexcept;
    htps::rptr<ITTFontFactory> getTTFontFactory() const noexcept;
    htps::rptr<IShaderFactory> getShaderFactory() const noexcept;
    htps::rptr<IBMPFontFactory> getBMPFontFactory() const noexcept;
    ITextureFactory& textureFactory() const;
    ITTFontFactory& ttfontFactory() const;
    IShaderFactory& shaderFactory() const;
    IBMPFontFactory& bmpFontFactory() const;

    bool isWindowFactoryAvailable() const noexcept;
    bool isTextureFactoryAvailable() const noexcept;
    bool isShaderFactoryAvailable() const noexcept;
    bool isBMPFontFactoryAvailable() const noexcept;
    bool isTTFontFactoryAvailable() const noexcept;

private:
    using BackendRegisterUptr = htps::uptr<BackendRegister>;
    htps::vector<BackendRegisterUptr>
        loaded_modules_;  //< List of loaded backend libraries.
    void selectFactoriesToUse(
        BackendRegisterUptr const& backend_register) noexcept;
    htps::rptr<IWindow> window_{nullptr};
    htps::rptr<ITextureFactory> textureFactory_{nullptr};
    htps::rptr<ITTFontFactory> ttfontFactory_{nullptr};
    htps::rptr<IShaderFactory> shaderFactory_{nullptr};
    htps::rptr<IBMPFontFactory> bmpFontFactory_{nullptr};
    htps::rptr<agl::Loader> loader_{nullptr};
};
}  // namespace haf::backend

#endif
