#ifndef HAF_SYSTEM_CONTROLLER_INCLUDE_HPP
#define HAF_SYSTEM_CONTROLLER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "systemprovider.hpp"
#include <haf/system/include/isystemcontroller.hpp>

namespace haf::sys
{
class SystemController final : public ISystemController, SystemProvider
{
public:
    SystemController();
    ~SystemController() override;

    void init(htps::rptr<IApp> iapp,
              int const argc,
              char const* const argv[]) override;
    bool runStep() override;
    void terminate() override;
};
}  // namespace haf::sys

#endif
