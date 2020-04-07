#pragma once

#ifndef HAF_BACKEND_AUTO_REGISTER_FACTORY_INLUDE_HPP
#define HAF_BACKEND_AUTO_REGISTER_FACTORY_INLUDE_HPP

#include "ibackendregister.hpp"

namespace haf::backend::client
{
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

        void create(mtps::uptr<IFactoryOf<T>> f)
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
        mtps::uptr<IFactoryOf<T>> factory_;

    };
}

#endif
