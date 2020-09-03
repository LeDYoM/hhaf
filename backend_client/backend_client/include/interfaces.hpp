#pragma once

#ifndef HAF_BACKEND_INTERFACES_INLUDE_HPP
#define HAF_BACKEND_INTERFACES_INLUDE_HPP

#include <mtypes/include/types.hpp>
#include <backend_client/include/ibackendregister.hpp>
#include <backend_client/include/autoregisterfactory.hpp>
#include <backend_client/include/ibackendmanager.hpp>
#include <backend_client/include/ifactory.hpp>

namespace haf::backend::client
{
void default_init_function_imp(IBackendManager* backend_manager,
                                  IBackendRegister* const ibackend_register)
{
    (*backend_manager).create();
    (*backend_manager).setFactories(ibackend_register);
}

template <typename T>
inline bool default_init_function(T** backend_manager,
                                  IBackendRegister* const ibackend_register)
{
    if (!(*backend_manager))
    {
        using BManager   = std::decay_t<T>;
        *backend_manager = new BManager;
        default_init_function_imp(*backend_manager, ibackend_register);
        return true;
    }
    return false;
}

inline void default_finish_function_imp(IBackendManager& backend_manager,
                                    IBackendRegister* const ibackend_register)
{
    backend_manager.resetFactories(ibackend_register);
    backend_manager.destroy();
}

template <typename T>
inline bool default_finish_function(T** backend_manager,
                                    IBackendRegister* const ibackend_register)
{
    if (*backend_manager)
    {
        default_finish_function_imp(**backend_manager, ibackend_register);
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
