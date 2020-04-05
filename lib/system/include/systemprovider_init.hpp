#pragma once

#ifndef LIB_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP
#define LIB_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP

#include <lib/system/include/icontrollablesystemprovider.hpp>

extern "C"
{
    IControllableSystemProvider *createSystemProvider();
    void destroySystemProvider(IControllableSystemProvider *);
}

#endif
