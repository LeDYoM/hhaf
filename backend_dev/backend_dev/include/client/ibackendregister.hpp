#pragma once

#ifndef HAF_BACKEND_BACKEND_REGISTER_INLUDE_HPP
#define HAF_BACKEND_BACKEND_REGISTER_INLUDE_HPP

#include "../iwindow.hpp"
#include "../irendertarget.hpp"
#include "../iresourcefactories.hpp"
#include "factory.hpp"

namespace haf::backend
{
using IWindowFactory         = IFactoryOf<IWindow>;
using IRenderTargetFactory   = IFactoryOf<IRenderTarget>;
using ITTFontFactoryFactory  = IFactoryOf<ITTFontFactory>;
using ITextureFactoryFactory = IFactoryOf<ITextureFactory>;
using IShaderFactoryFactory  = IFactoryOf<IShaderFactory>;
using IBMPFontFactoryFactory = IFactoryOf<IBMPFontFactory>;

namespace client
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
}

}  // namespace haf::backend::client

#endif
