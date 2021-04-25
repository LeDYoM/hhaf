#ifndef HAF_BACKEND_AUTO_REGISTER_FACTORY_INLUDE_HPP
#define HAF_BACKEND_AUTO_REGISTER_FACTORY_INLUDE_HPP

#include "ibackendregister.hpp"

namespace haf::backend::client
{
class IAutoRegisterFactory
{
public:
    virtual ~IAutoRegisterFactory() {}
    virtual void setFactory(IBackendRegister* const backend_register) const = 0;
    virtual void resetFactory(
        IBackendRegister* const backend_register) const = 0;
    virtual void destroy()                              = 0;
};

template <typename T>
class AutoRegisterFactory : public IAutoRegisterFactory
{
public:
    AutoRegisterFactory() noexcept : factory_{} {}

    void create(htps::uptr<IFactoryOf<T>> f) { factory_ = std::move(f); }

    void setFactory(IBackendRegister* const backend_register) const override
    {
        backend_register->setFactory(factory_.get());
    }

    void resetFactory(IBackendRegister* const backend_register) const override
    {
        backend_register->setFactory(static_cast<IFactoryOf<T>*>(nullptr));
    }

    void destroy() override { factory_.reset(); }

private:
    htps::uptr<IFactoryOf<T>> factory_;
};
}  // namespace haf::backend::client

#endif
