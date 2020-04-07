#pragma once

#ifndef HAF_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP

#include <lib/system/include/icontrollablesystemprovider.hpp>

extern "C"
{
    IControllableSystemProvider *createSystemProvider();
    void destroySystemProvider(IControllableSystemProvider *);
}

#endif
