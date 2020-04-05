#pragma once

#ifndef LIB_BACKEND_IBACKEND_MANAGER_INLUDE_HPP
#define LIB_BACKEND_IBACKEND_MANAGER_INLUDE_HPP

#include "ibackendregister.hpp"

namespace haf::backend::client
{
struct IBackendManager
{
    virtual void create() = 0;
    virtual void setFactories(IBackendRegister *const) = 0;
    virtual void resetFactories(IBackendRegister *const backend_register) = 0;
    virtual void destroy() = 0;
    virtual ~IBackendManager() {}
};
} // namespace haf::backend::client

#endif