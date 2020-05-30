#pragma once

#ifndef HAF_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_PROVIDER_INIT_C_INTERFACE_INCLUDE_HPP

#include <haf/system/include/isystemcontroller.hpp>

extern "C" __declspec(dllexport) ISystemController* createSystemController();
extern "C" __declspec(dllexport) void destroySystemController(
    ISystemController*);

#endif
