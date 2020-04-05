#pragma once

#ifndef LIB_BACKEND_BACKEND_REGISTER_INLUDE_HPP
#define LIB_BACKEND_BACKEND_REGISTER_INLUDE_HPP

#include "../iwindow.hpp"
#include "../iresourcefactories.hpp"
#include "factory.hpp"

namespace haf::backend
{
    using IInfoFactory = IFactoryOf<IWindowProviderInfo>;
    using IWindowFactory = IFactoryOf<IWindow>;
    using ITTFontFactoryFactory = IFactoryOf<ITTFontFactory>;
    using ITextureFactoryFactory = IFactoryOf<ITextureFactory>;
    using IShaderFactoryFactory = IFactoryOf<IShaderFactory>;
    using IBMPFontFactoryFactory = IFactoryOf<IBMPFontFactory>;

    class IBackendRegister
    {
    public:
        virtual void setFactory(IInfoFactory* const) noexcept = 0;
        virtual void setFactory(IWindowFactory* const) noexcept = 0;
        virtual void setFactory(ITTFontFactoryFactory* const) noexcept = 0;
        virtual void setFactory(ITextureFactoryFactory* const) noexcept = 0;
        virtual void setFactory(IShaderFactoryFactory* const) noexcept = 0;
        virtual void setFactory(IBMPFontFactoryFactory* const) noexcept = 0;

        virtual ~IBackendRegister() {}
    };
}

#endif
