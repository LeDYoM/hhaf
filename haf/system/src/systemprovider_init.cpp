#include "systemprovider_init.hpp"
#include "systemcontroller.hpp"

ISystemController* createSystemController()
{
    using namespace haf::sys;
    return new SystemController();
}

void destroySystemController(ISystemController* isp)
{
    auto system_controller = dynamic_cast<haf::sys::SystemController*>(isp);
    delete system_controller;
}
