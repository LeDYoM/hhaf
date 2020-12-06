#ifndef HAF_BACKEND_IBACKEND_MANAGER_INLUDE_HPP
#define HAF_BACKEND_IBACKEND_MANAGER_INLUDE_HPP

#include "ibackendregister.hpp"
#include <backend_client/include/backend_client_exports.hpp>

namespace haf::backend::client
{
/**
 * @brief Abstact class to derive concrete backend managers.
 */
class  BC_API IBackendManager
{
public:
    virtual void create() = 0;
    virtual void setFactories(IBackendRegister *const) = 0;
    virtual void resetFactories(IBackendRegister *const backend_register) = 0;
    virtual void destroy() = 0;
    virtual ~IBackendManager() {}
};
} // namespace haf::backend::client

#endif
