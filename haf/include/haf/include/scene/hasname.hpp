#ifndef HAF_SCENE_HASNAME_HPP
#define HAF_SCENE_HASNAME_HPP

#include <htypes/include/str.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::sys
{
class HAF_API HasName
{
public:
    constexpr HasName(htps::str const& name) : name_{name} {}
    constexpr HasName(htps::str&& name) noexcept : name_{std::move(name)} {}
    constexpr HasName(HasName&& other) noexcept = default;
    constexpr HasName(HasName const& other)     = default;
    constexpr HasName& operator=(HasName&& other) noexcept = default;
    constexpr HasName& operator=(HasName const& other) = default;

    constexpr htps::str const& name() const noexcept { return name_; }

protected:
    constexpr ~HasName() = default;

private:
    htps::str name_;
};
}  // namespace haf::sys

#endif
