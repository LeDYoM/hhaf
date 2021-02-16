#ifndef HAF_USER_IAPP_WITH_DEFAULT_VERSIONING_SYSTEM_INCLUDE_HPP
#define HAF_USER_IAPP_WITH_DEFAULT_VERSIONING_SYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <hosted_app/include/iapp.hpp>

namespace haf::user
{
template <typename VersionClass>
class IAppWithDefaultVersionSystem : public haf::IApp
{
public:
    mtps::u16 getVersion() const noexcept override  { return VersionClass::VersionMajor; }
    mtps::u16 getSubVersion() const noexcept override { return VersionClass::VersionMinor; }
    mtps::u16 getPatch() const noexcept override { return VersionClass::VersionPatch; }
    mtps::u16 getTweak() const noexcept override { return VersionClass::VersionTweak; }
    mtps::str getName() const noexcept override { return VersionClass::ProjectName; }
};
}  // namespace haf::user

#endif
