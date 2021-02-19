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
    htps::u16 getVersion() const noexcept override  { return VersionClass::VersionMajor; }
    htps::u16 getSubVersion() const noexcept override { return VersionClass::VersionMinor; }
    htps::u16 getPatch() const noexcept override { return VersionClass::VersionPatch; }
    htps::u16 getTweak() const noexcept override { return VersionClass::VersionTweak; }
    htps::str getName() const noexcept override { return VersionClass::ProjectName; }
};
}  // namespace haf::user

#endif
