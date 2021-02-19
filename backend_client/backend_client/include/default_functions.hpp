#ifndef HAF_BACKEND_CLIENT_DEFAULT_FUNCTIONS_INLUDE_HPP
#define HAF_BACKEND_CLIENT_DEFAULT_FUNCTIONS_INLUDE_HPP

#include <htypes/include/types.hpp>
#include <backend_client/include/ibackendregister.hpp>
#include <backend_client/include/autoregisterfactory.hpp>
#include <backend_client/include/ibackendmanager.hpp>

namespace haf::backend::client
{
void default_init_function_imp(
    htps::rptr<IBackendManager> backend_manager,
    htps::rptr<IBackendRegister> const ibackend_register);

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

void default_finish_function_imp(
    IBackendManager& backend_manager,
    htps::rptr<IBackendRegister> const ibackend_register);

template <typename T>
inline bool default_finish_function(
    T** backend_manager,
    htps::rptr<IBackendRegister> const ibackend_register)
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

#endif
