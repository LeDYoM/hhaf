#pragma once

#ifndef HAF_SYSTEM_CONTROLLER_INCLUDE_HPP
#define HAF_SYSTEM_CONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "systemprovider.hpp"
#include <haf/system/include/isystemcontroller.hpp>

namespace haf::sys
{
class SystemController final : public ISystemController, SystemProvider
{
public:
    SystemController();
    ~SystemController() override;

    void init(mtps::rptr<IApp> iapp) override;
    bool runStep() override;
    void terminate() override;
};
}  // namespace haf::sys

#endif
