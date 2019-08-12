#pragma once

#ifndef LIB_BACKEND_INTERFACES_INLUDE_HPP
#define LIB_BACKEND_INTERFACES_INLUDE_HPP

#include "iwindow.hpp"
#include "iresourcefactories.hpp"
#include "factory.hpp"

namespace lib::backend
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

    struct IBackendManager
    {
        virtual void create() = 0;
        virtual void setFactories(lib::backend::IBackendRegister*const) = 0;
        virtual void resetFactories(lib::backend::IBackendRegister*const backend_register) = 0;
        virtual void destroy() = 0;
        virtual ~IBackendManager() { }
    };

    class IAutoRegisterFactory
    {
    public:
        virtual void setFactory(IBackendRegister*const backend_register) = 0;
        virtual void resetFactory(IBackendRegister*const backend_register) = 0;
        virtual void destroy() = 0;
    };

    template <typename T>
    class AutoRegisterFactory : public IAutoRegisterFactory
    {
    public:
        AutoRegisterFactory() noexcept : factory_{} {}

        void create(uptr<IFactoryOf<T>> f)
        {
            factory_ = std::move(f);
        }

        void setFactory(IBackendRegister*const backend_register) override
        {
            backend_register->setFactory(factory_.get());
        }

        void resetFactory(IBackendRegister*const backend_register) override
        {
            backend_register->setFactory(static_cast<IFactoryOf<T>*>(nullptr));
        }

        void destroy() override
        {
            factory_.reset();
        }
    private:
        uptr<IFactoryOf<T>> factory_;

    };
}

using p_initLib = bool (*)(lib::backend::IBackendRegister* const);
using p_finishLib = bool (*)(lib::backend::IBackendRegister* const);

#endif
