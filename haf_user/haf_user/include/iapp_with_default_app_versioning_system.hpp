#ifndef HAF_USER_IAPP_WITH_DEFAULT_VERSIONING_SYSTEM_INCLUDE_HPP
#define HAF_USER_IAPP_WITH_DEFAULT_VERSIONING_SYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <hosted_app/include/iapp.hpp>

namespace haf::user
{
template <htps::size_type Version,
          htps::size_type SubVersion,
          htps::size_type Patch,
          htps::size_type Tweak,
          htps::str_view Holder,
          typename Base = haf::IApp>
class IAppWithDefaultVersionSystem : public Base
{
public:
    htps::u16 getVersion() const noexcept override { return Version; }
    htps::u16 getSubVersion() const noexcept override { return SubVersion; }
    htps::u16 getPatch() const noexcept override { return Patch; }
    htps::u16 getTweak() const noexcept override { return Tweak; }
    htps::str getName() const noexcept { return htps::str{Holder.data()}; }    
};
}  // namespace haf::user

#endif
