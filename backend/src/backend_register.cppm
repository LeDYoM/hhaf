module;

#include <type_traits>
#include <concepts>

export module backend:backend_register;

import htypes;
import backend_dev;
import :backend_log;

export using p_initBackendClient =
    bool (*)(haf::backend::client::IBackendRegister* const);
export using p_finishBackendClient =
    bool (*)(haf::backend::client::IBackendRegister* const);

namespace haf::backend
{
class BackendRegister;

export template <typename FactoryType>
bool fillFactory(htps::rptr<BackendRegister> const& backend_register,
                 FactoryType** factory_to_fill);

export template <typename FactoryType, typename... FactoryTypes>
bool fillFactories(htps::rptr<BackendRegister> const& backend_register,
                   FactoryType factory_to_fill,
                   FactoryTypes... factories_to_fill)
{
    bool result{fillFactory(backend_register, factory_to_fill)};

    if constexpr (sizeof...(FactoryTypes) > 0U)
    {
        result |= fillFactories(backend_register, factories_to_fill...);
    }

    return result;
}

export template <typename FactoryType>
bool emptyFactory(htps::rptr<BackendRegister> const& backend_register,
                  FactoryType** factory_to_empty);

export template <typename FactoryType, typename... FactoryTypes>
bool emptyFactories(htps::rptr<BackendRegister> const& backend_register,
                    FactoryType factory_to_empty,
                    FactoryTypes... factories_to_empty)
{
    bool result{emptyFactory(backend_register, factory_to_empty)};

    if constexpr (sizeof...(FactoryTypes) > 0U)
    {
        result |= emptyFactories(backend_register, factories_to_empty...);
    }

    return result;
}

export class BackendRegister final : public client::IBackendRegister
{
public:
    explicit BackendRegister(htps::str const& module_name) :
        module_name_{module_name}
    {}

    void setFactory(htps::uptr<IWindowFactory> window_factory) noexcept
    {
        window_factory_ = htps::move(window_factory);
    }

    void setFactory(
        htps::uptr<ITTFontFactoryFactory> ttfont_factory_factory) noexcept
    {
        ttfont_factory_factory_ = htps::move(ttfont_factory_factory);
    }

    void setFactory(
        htps::uptr<ITextureFactoryFactory> texture_factory_factory) noexcept
    {
        texture_factory_factory_ = htps::move(texture_factory_factory);
    }

    void setFactory(
        htps::uptr<IShaderFactoryFactory> shader_factory_factory) noexcept
    {
        shader_factory_factory_ = htps::move(shader_factory_factory);
    }

    void setFactory(
        htps::uptr<IBMPFontFactoryFactory> bmpfont_factory_factory) noexcept
    {
        bmpfont_factory_factory_ = htps::move(bmpfont_factory_factory);
    }

    void setLibFuncs(p_initBackendClient init_lib_func,
                     p_finishBackendClient finish_lib_func) noexcept
    {
        init_lib_func_   = init_lib_func;
        finish_lib_func_ = finish_lib_func;
    }

    template <typename T>
        requires std::is_same_v<T, IFactoryOf<IWindow>>
    htps::sptr<IWindowFactory> getFactory()
    {
        return window_factory_;
    }

    template <typename T>
        requires std::is_same_v<T, IFactoryOf<ITTFontFactory>>
    htps::sptr<ITTFontFactoryFactory> getFactory() const
    {
        return ttfont_factory_factory_;
    }

    template <typename T>
        requires std::is_same_v<T, IFactoryOf<ITextureFactory>>
    htps::sptr<ITextureFactoryFactory> getFactory() const
    {
        return texture_factory_factory_;
    }

    template <typename T>
        requires std::is_same_v<T, IFactoryOf<IShaderFactory>>
    htps::sptr<IShaderFactoryFactory> getFactory() const
    {
        return shader_factory_factory_;
    }

    template <typename T>
        requires std::is_same_v<T, IFactoryOf<IBMPFontFactory>>
    htps::sptr<IBMPFontFactoryFactory> getFactory() const
    {
        return bmpfont_factory_factory_;
    }

    bool init()
    {
        if (canUse())
        {
            const bool result{init_lib_func_(this)};
            return result;
        }
        return false;
    }

    bool finish()
    {
        if (finish_lib_func_)
        {
            return finish_lib_func_(this);
        }
        return false;
    }

    bool canUse() const noexcept
    {
        return init_lib_func_ != nullptr && finish_lib_func_ != nullptr;
    }

    bool fillRegisteredFactories()
    {
        return fillFactories(this, &window_, &ttfontFactory_, &textureFactory_,
                             &shaderFactory_, &bmpFontFactory_);
    }

    bool emptyRegisteredFactories()
    {
        return emptyFactories(this, &window_, &textureFactory_, &ttfontFactory_,
                              &shaderFactory_, &bmpFontFactory_);
    }

    htps::str const& moduleName() const noexcept { return module_name_; }

    htps::rptr<IWindow> window_{nullptr};
    htps::rptr<ITextureFactory> textureFactory_{nullptr};
    htps::rptr<ITTFontFactory> ttfontFactory_{nullptr};
    htps::rptr<IShaderFactory> shaderFactory_{nullptr};
    htps::rptr<IBMPFontFactory> bmpFontFactory_{nullptr};

private:
    htps::str module_name_{};
    p_initBackendClient init_lib_func_{nullptr};
    p_finishBackendClient finish_lib_func_{nullptr};
    htps::sptr<IWindowFactory> window_factory_;
    htps::sptr<ITTFontFactoryFactory> ttfont_factory_factory_;
    htps::sptr<ITextureFactoryFactory> texture_factory_factory_;
    htps::sptr<IShaderFactoryFactory> shader_factory_factory_;
    htps::sptr<IBMPFontFactoryFactory> bmpfont_factory_factory_;
};

export template <typename FactoryType>
bool fillFactory(htps::rptr<BackendRegister> const& backend_register,
                 FactoryType** factory_to_fill)
{
    if (auto factory{backend_register->getFactory<IFactoryOf<FactoryType>>()};
        factory != nullptr)
    {
        // TODO: Re-eanble
        //        (*factory_to_fill) = factory->create();
        return (*factory_to_fill) != nullptr;
    }
    return true;
}

export template <typename FactoryType>
bool emptyFactory(htps::rptr<BackendRegister> const& backend_register,
                  FactoryType** factory_to_empty)
{
    if (auto factory{backend_register->getFactory<IFactoryOf<FactoryType>>()};
        factory != nullptr)
    {
        if (factory_to_empty != nullptr && *factory_to_empty != nullptr)
        {
        // TODO: Re-eanble
//            factory->destroy(*factory_to_empty);
            (*factory_to_empty) = nullptr;
            return true;
        }
    }
    return true;
}

}  // namespace haf::backend
