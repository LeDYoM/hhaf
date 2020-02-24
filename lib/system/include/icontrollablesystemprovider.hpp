#pragma once

#ifndef LIB_ICONTROLLABLE_ISYSTEM_PROVIDER_INTERFACE_INCLUDE_HPP
#define LIB_ICONTROLLABLE_ISYSTEM_PROVIDER_INTERFACE_INCLUDE_HPP

namespace lib
{
class IApp;
}

class IControllableSystemProvider
{
public:
    virtual ~IControllableSystemProvider() {}

    virtual void init(lib::IApp *iapp) = 0;
    virtual bool runStep() = 0;
    virtual void terminate() = 0;
};

#endif
