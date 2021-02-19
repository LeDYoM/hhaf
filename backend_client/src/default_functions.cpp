#include <backend_client/include/default_functions.hpp>

#include <htypes/include/types.hpp>
#include <backend_client/include/ibackendregister.hpp>
#include <backend_client/include/ibackendmanager.hpp>

namespace haf::backend::client
{
void default_init_function_imp(
    htps::rptr<IBackendManager> backend_manager,
    htps::rptr<IBackendRegister> const ibackend_register)
{
    (*backend_manager).create();
    (*backend_manager).setFactories(ibackend_register);
}

void default_finish_function_imp(
    IBackendManager& backend_manager,
    htps::rptr<IBackendRegister> const ibackend_register)
{
    backend_manager.resetFactories(ibackend_register);
    backend_manager.destroy();
}

}  // namespace haf::backend::client
