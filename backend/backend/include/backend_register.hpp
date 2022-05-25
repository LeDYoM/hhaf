#ifndef HAF_BACKEND_REGISTER_INCLUDE_HPP
#define HAF_BACKEND_REGISTER_INCLUDE_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/ibackendregister.hpp>

using p_initBackendClient =
    bool (*)(haf::backend::client::IBackendRegister* const);
using p_finishBackendClient =
    bool (*)(haf::backend::client::IBackendRegister* const);

namespace haf::backend
{
class BackendRegister final : public client::IBackendRegister
{
public:
    void setFactory(htps::uptr<IWindowFactory>) noexcept override;
    void setFactory(htps::uptr<IRenderTargetFactory>) noexcept override;
    void setFactory(htps::uptr<ITTFontFactoryFactory>) noexcept override;
    void setFactory(htps::uptr<ITextureFactoryFactory>) noexcept override;
    void setFactory(htps::uptr<IShaderFactoryFactory>) noexcept override;
    void setFactory(htps::uptr<IBMPFontFactoryFactory>) noexcept override;

    void setLibFuncs(p_initBackendClient init_lib_func,
                     p_finishBackendClient finish_lib_func) noexcept;

    template <typename T,
              typename = std::enable_if_t<std::is_same_v<T, IWindowFactory>>>
    htps::sptr<IWindowFactory> getFactory()
    {
        return window_factory_;
    }

    template <
        typename T,
        typename = std::enable_if_t<std::is_same_v<T, ITTFontFactoryFactory>>>
    htps::sptr<ITTFontFactoryFactory> getFactory() const
    {
        return ttfont_factory_factory_;
    }

    template <
        typename T,
        typename = std::enable_if_t<std::is_same_v<T, ITextureFactoryFactory>>>
    htps::sptr<ITextureFactoryFactory> getFactory() const
    {
        return texture_factory_factory_;
    }

    template <
        typename T,
        typename = std::enable_if_t<std::is_same_v<T, IShaderFactoryFactory>>>
    htps::sptr<IShaderFactoryFactory> getFactory() const
    {
        return shader_factory_factory_;
    }

    template <
        typename T,
        typename = std::enable_if_t<std::is_same_v<T, IBMPFontFactoryFactory>>>
    htps::sptr<IBMPFontFactoryFactory> getFactory() const
    {
        return bmpfont_factory_factory_;
    }

    bool init();
    bool finish();

    inline bool canUse() const noexcept
    {
        return init_lib_func_ != nullptr && finish_lib_func_ != nullptr;
    }

    bool fillRegisteredFactories();
    bool emptyRegisteredFactories();

    htps::rptr<IWindow> window_{nullptr};
    htps::rptr<IRenderTarget> render_target_{nullptr};
    htps::rptr<ITextureFactory> textureFactory_{nullptr};
    htps::rptr<ITTFontFactory> ttfontFactory_{nullptr};
    htps::rptr<IShaderFactory> shaderFactory_{nullptr};
    htps::rptr<IBMPFontFactory> bmpFontFactory_{nullptr};

private:
    p_initBackendClient init_lib_func_{nullptr};
    p_finishBackendClient finish_lib_func_{nullptr};
    htps::sptr<IWindowFactory> window_factory_;
    htps::sptr<IRenderTargetFactory> render_target_factory_;
    htps::sptr<ITTFontFactoryFactory> ttfont_factory_factory_;
    htps::sptr<ITextureFactoryFactory> texture_factory_factory_;
    htps::sptr<IShaderFactoryFactory> shader_factory_factory_;
    htps::sptr<IBMPFontFactoryFactory> bmpfont_factory_factory_;
};
}  // namespace haf::backend

#endif
