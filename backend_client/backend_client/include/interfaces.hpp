#pragma once

#ifndef HAF_BACKEND_INTERFACES_INLUDE_HPP
#define HAF_BACKEND_INTERFACES_INLUDE_HPP

#include "ibackendregister.hpp"
#include "autoregisterfactory.hpp"
#include "ibackendmanager.hpp"
#include "factory.hpp"

namespace haf::backend::client
{

class DefaultBackendManager : public IBackendManager
{
public:
    template <typename T>
    void createFactoryOfFactories()
    {
        auto f(mtps::muptr<AutoRegisterFactory<typename T::Interface>>());
        f.get()->create(mtps::muptr<T>());
        factories.push_back(std::move(f));
    }

    void setFactories(IBackendRegister* const backend_register) override final
    {
        for (auto const& factory : factories)
        {
            factory.get()->setFactory(backend_register);
        }
    }

    void resetFactories(
        IBackendRegister* const backend_register) override final
    {
        for (auto const& factory : factories)
        {
            factory.get()->resetFactory(backend_register);
        }
    }

    void destroy() override final
    {
        for (const auto& factory : factories)
        {
            factory.get()->destroy();
        }
    }

    ~DefaultBackendManager() override { destroy(); }

private:
    mtps::vector<mtps::uptr<IAutoRegisterFactory>> factories;
};

template <typename T>
inline bool default_init_function(T** backend_manager,
                                  IBackendRegister* const ibackend_register)
{
    if (!(*backend_manager))
    {
        using BManager = std::decay_t<T>;
        *backend_manager = new BManager;
        (*backend_manager)->create();

        (*backend_manager)->setFactories(ibackend_register);
        return true;
    }
    return false;
}

template <typename T>
inline bool default_finish_function(T** backend_manager,
                                    IBackendRegister* const ibackend_register)
{
    if (*backend_manager)
    {
        (*backend_manager)->resetFactories(ibackend_register);
        (*backend_manager)->destroy();
        delete (*backend_manager);
        (*backend_manager) = nullptr;
        return true;
    }

    return false;
}
}  // namespace haf::backend::client

using p_initHaf   = bool (*)(haf::backend::client::IBackendRegister* const);
using p_finishHaf = bool (*)(haf::backend::client::IBackendRegister* const);

#endif
