#pragma once

#ifndef HAF_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP

#include <haf/system/include/isystemcontroller.hpp>

extern "C"
{
    ISystemController *createSystemController();
    void destroySystemController(ISystemController *);
}

#endif
