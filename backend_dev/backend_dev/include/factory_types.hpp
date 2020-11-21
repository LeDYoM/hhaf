#pragma once

#ifndef HAF_BACKEND_FACTORY_TYPES_INLUDE_HPP
#define HAF_BACKEND_FACTORY_TYPES_INLUDE_HPP

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/irendertarget.hpp>
#include <backend_dev/include/iresourcefactories.hpp>
#include <backend_dev/include/ifactory.hpp>

namespace haf::backend
{
using IWindowFactory         = IFactoryOf<IWindow>;
using IRenderTargetFactory   = IFactoryOf<IRenderTarget>;
using ITTFontFactoryFactory  = IFactoryOf<ITTFontFactory>;
using ITextureFactoryFactory = IFactoryOf<ITextureFactory>;
using IShaderFactoryFactory  = IFactoryOf<IShaderFactory>;
using IBMPFontFactoryFactory = IFactoryOf<IBMPFontFactory>;

}  // namespace haf::backend

#endif
