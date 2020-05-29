#pragma once

#ifndef HAF_BACKEND_REGISTER_INCLUDE_HPP
#define HAF_BACKEND_REGISTER_INCLUDE_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/client/ibackendregister.hpp>
#include <backend_dev/include/client/interfaces.hpp>

namespace haf::backend
{
class BackendRegister final : public IBackendRegister
{
public:
    void setFactory(IWindowFactory* const) noexcept override;
    void setFactory(ITTFontFactoryFactory* const) noexcept override;
    void setFactory(ITextureFactoryFactory* const) noexcept override;
    void setFactory(IShaderFactoryFactory* const) noexcept override;
    void setFactory(IBMPFontFactoryFactory* const) noexcept override;

    void setLibFuncs(p_initHaf init_lib_func,
                     p_finishHaf finish_lib_func) noexcept;

    template <typename T>
    T* const getFactory() const;

    template <>
    IWindowFactory* const getFactory() const
    {
        return window_factory_;
    }
    template <>
    ITTFontFactoryFactory* const getFactory() const
    {
        return ttfont_factory_factory_;
    }
    template <>
    ITextureFactoryFactory* const getFactory() const
    {
        return texture_factory_factory_;
    }
    template <>
    IShaderFactoryFactory* const getFactory() const
    {
        return shader_factory_factory_;
    }
    template <>
    IBMPFontFactoryFactory* const getFactory() const
    {
        return bmpfont_factory_factory_;
    }

    bool init();
    bool finish();

    inline bool canUse() const noexcept
    {
        return init_lib_func_ != nullptr && finish_lib_func_ != nullptr;
    }

private:
    p_initHaf init_lib_func_{nullptr};
    p_finishHaf finish_lib_func_{nullptr};
    IWindowFactory* window_factory_{nullptr};
    ITTFontFactoryFactory* ttfont_factory_factory_{nullptr};
    ITextureFactoryFactory* texture_factory_factory_{nullptr};
    IShaderFactoryFactory* shader_factory_factory_{nullptr};
    IBMPFontFactoryFactory* bmpfont_factory_factory_{nullptr};
};
}  // namespace haf::backend

#endif
