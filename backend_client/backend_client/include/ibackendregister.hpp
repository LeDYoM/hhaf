#pragma once

#ifndef HAF_BACKEND_BACKEND_REGISTER_INLUDE_HPP
#define HAF_BACKEND_BACKEND_REGISTER_INLUDE_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/factory_types.hpp>
#include <backend_dev/include/ifactory.hpp>

namespace haf::backend::client
{
class IBackendRegister
{
public:
    virtual void setFactory(IWindowFactory* const) noexcept         = 0;
    virtual void setFactory(IRenderTargetFactory* const) noexcept   = 0;
    virtual void setFactory(ITTFontFactoryFactory* const) noexcept  = 0;
    virtual void setFactory(ITextureFactoryFactory* const) noexcept = 0;
    virtual void setFactory(IShaderFactoryFactory* const) noexcept  = 0;
    virtual void setFactory(IBMPFontFactoryFactory* const) noexcept = 0;

    virtual ~IBackendRegister() {}
};

}  // namespace haf::backend::client

#endif
