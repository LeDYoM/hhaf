#ifndef HAF_BACKEND_AUTO_REGISTER_FACTORY_INLUDE_HPP
#define HAF_BACKEND_AUTO_REGISTER_FACTORY_INLUDE_HPP

#include <backend_dev/include/ifactory.hpp>
#include <backend_dev/include/ibackendregister.hpp>

namespace haf::backend::client
{
class IAutoRegisterFactory
{
public:
    virtual ~IAutoRegisterFactory() {}
    virtual void setFactory(
        IBackendRegister* const backend_register) noexcept = 0;
    virtual void resetFactory(
        IBackendRegister* const backend_register) const noexcept = 0;
    virtual void destroy() noexcept                              = 0;
};

template <typename T>
class AutoRegisterFactory : public IAutoRegisterFactory
{
public:
    constexpr AutoRegisterFactory() noexcept : factory_{} {}

    void create(htps::uptr<IFactoryOf<T>> f) { factory_ = std::move(f); }

    void setFactory(IBackendRegister* const backend_register) noexcept override
    {
        backend_register->setFactory(std::move(factory_));
    }

    void resetFactory(
        IBackendRegister* const backend_register) const noexcept override
    {
        backend_register->setFactory(std::unique_ptr<IFactoryOf<T>>{});
    }

    void destroy() noexcept override { factory_.reset(); }

private:
    htps::uptr<IFactoryOf<T>> factory_;
};
}  // namespace haf::backend::client

#endif
