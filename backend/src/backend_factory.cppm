export module backend:backend_factory;

import :backend_register;
import :backend_log;

import htypes;
import agloader;
import backend_dev;

namespace haf::backend
{
/**
 * @brief Class representing a factory for backend classes.
 * This class initializes and stores subsystems of a backend.
 */
class BackendFactory final
{
public:
    BackendFactory() :
        window_{nullptr},
        textureFactory_{nullptr},
        ttfontFactory_{nullptr},
        shaderFactory_{nullptr},
        bmpFontFactory_{nullptr},
        loader_{agl::createLoader()}
    {}

    ~BackendFactory()
    {
        BackendLogDisplayer::debug("Destroying backend factory");
        for (auto&& loaded_module : loaded_modules_)
        {
            BackendLogDisplayer::debug("Destroying backend loaded module: ",
                                       loaded_module->moduleName());
            loaded_module->emptyRegisteredFactories();
            loaded_module->finish();
            loader_->unloadModule(loaded_module->moduleName().c_str());
            loaded_module.reset();
        }
        loaded_modules_.clear();

        agl::destroyLoader();
        loader_ = nullptr;
        BackendLogDisplayer::debug("backend factory destroyed");
    }

    /**
     * @brief Load a new shared object containing factories to be used by haf
     *
     * @param file_name File name containing the backend factories library to
     * load
     * @return true Successfully load
     * @return false Failed in loading
     */
    bool loadBackendFile(htps::str const& file_name)
    {
        BackendLogDisplayer::debug("Going to load backend module: ", file_name);

        if (loader_->loadModule(file_name.c_str()))
        {
            // Get the function pointer to load and unload the backend module
            auto const fp_init_backend_client_library{
                loader_->loadMethod<p_initBackendClient>(file_name.c_str(),
                                                         "init_lib")};
            auto const fp_finish_backend_client_library{
                loader_->loadMethod<p_initBackendClient>(file_name.c_str(),
                                                         "finish_lib")};

            if (fp_init_backend_client_library != nullptr &&
                fp_finish_backend_client_library != nullptr)
            {
                // The loaded client library contains init and destroy
                BackendRegisterUptr backend_register{
                    muptr<BackendRegister>(file_name)};

                backend_register->setLibFuncs(fp_init_backend_client_library,
                                              fp_finish_backend_client_library);
                if (backend_register->init())
                {
                    bool const result{
                        backend_register->fillRegisteredFactories()};

                    if (result)
                    {
                        selectFactoriesToUse(backend_register);
                        loaded_modules_.push_back(htps::move(backend_register));
                    }
                    return result;
                }
            }
        }
        return false;
    }

    template <typename T>
    void updateFactory(T*& global_factory, T* const registered_factory) noexcept
    {
        if (global_factory == nullptr)
        {
            global_factory = registered_factory;
        }
    }

    htps::rptr<IWindow> getWindow() const noexcept { return window_; }
    htps::rptr<ITextureFactory> getTextureFactory() const noexcept
    {
        return textureFactory_;
    }

    htps::rptr<ITTFontFactory> getTTFontFactory() const noexcept
    {
        return ttfontFactory_;
    }

    htps::rptr<IShaderFactory> getShaderFactory() const noexcept
    {
        return shaderFactory_;
    }

    htps::rptr<IBMPFontFactory> getBMPFontFactory() const noexcept
    {
        return bmpFontFactory_;
    }

    ITextureFactory& textureFactory() const
    {
        return *getTextureFactory();
    }

    ITTFontFactory& ttfontFactory() const
    {
        return *getTTFontFactory();
    }

    IShaderFactory& shaderFactory() const
    {
        return *getShaderFactory();
    }

    IBMPFontFactory& bmpFontFactory() const
    {
        return *getBMPFontFactory();
    }

    bool isWindowFactoryAvailable() const noexcept
    {
        return window_ != nullptr;
    }

    bool isTextureFactoryAvailable() const noexcept
    {
        return textureFactory_ != nullptr;
    }

    bool isShaderFactoryAvailable() const noexcept
    {
        return shaderFactory_ != nullptr;
    }

    bool isBMPFontFactoryAvailable() const noexcept
    {
        return bmpFontFactory_ != nullptr;
    }

    bool isTTFontFactoryAvailable() const noexcept
    {
        return ttfontFactory_ != nullptr;
    }

private:
    using BackendRegisterUptr = htps::uptr<BackendRegister>;
    htps::vector<BackendRegisterUptr>
        loaded_modules_;  //< List of loaded backend libraries.
    void selectFactoriesToUse(
        BackendRegisterUptr const& backend_register) noexcept
    {
        updateFactory(window_, backend_register->window_);
        updateFactory(ttfontFactory_, backend_register->ttfontFactory_);
        updateFactory(bmpFontFactory_, backend_register->bmpFontFactory_);
        updateFactory(textureFactory_, backend_register->textureFactory_);
        updateFactory(shaderFactory_, backend_register->shaderFactory_);
    }

    htps::rptr<IWindow> window_{nullptr};
    htps::rptr<ITextureFactory> textureFactory_{nullptr};
    htps::rptr<ITTFontFactory> ttfontFactory_{nullptr};
    htps::rptr<IShaderFactory> shaderFactory_{nullptr};
    htps::rptr<IBMPFontFactory> bmpFontFactory_{nullptr};
    htps::rptr<agl::Loader> loader_{nullptr};
};
}  // namespace haf::backend
