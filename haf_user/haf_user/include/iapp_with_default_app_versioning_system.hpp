#ifndef HAF_USER_IAPP_WITH_DEFAULT_VERSIONING_SYSTEM_INCLUDE_HPP
#define HAF_USER_IAPP_WITH_DEFAULT_VERSIONING_SYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <hosted_app/include/iapp.hpp>

namespace haf::user
{
class IAppWithDefaultVersionSystem : public haf::IApp
{
public:
    mtps::u16 getVersion() const noexcept override  { return 2U; }
    mtps::u16 getSubVersion() const noexcept override { return 1; }
    mtps::u16 getPatch() const noexcept override { return 1; }
    mtps::u16 getTweak() const noexcept override { return 1; }
    mtps::str getName() const noexcept override { return "aaaa"; }
};
}  // namespace haf::user

#endif
