#include "systemprovider_init.hpp"
#include <lib/system/i_include/systemprovider.hpp>

IControllableSystemProvider* createSystemProvider()
{
    using namespace haf::sys;
    return new SystemProvider();
}

void destroySystemProvider(IControllableSystemProvider* isp)
{
    auto system_provider = dynamic_cast<haf::sys::SystemProvider*>(isp);
    delete system_provider;
}
