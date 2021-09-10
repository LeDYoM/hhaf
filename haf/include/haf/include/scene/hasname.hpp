#ifndef HAF_SCENE_HASNAME_HPP
#define HAF_SCENE_HASNAME_HPP

#include <htypes/include/str.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::sys
{
class HAF_API HasName
{
public:
    constexpr HasName(htps::str const& name) noexcept : name_(name) {}
    constexpr HasName(htps::str&& name) noexcept : name_(std::move(name)) {}
    constexpr HasName(HasName&& other) noexcept = default;
    constexpr HasName(const HasName& other)     = default;
    HasName& operator=(HasName&& other) noexcept = default;
    HasName& operator=(const HasName& other) = default;

    htps::str const& name() const noexcept { return name_; }

protected:
    ~HasName() {}

private:
    htps::str name_;
};
}  // namespace haf::sys

#endif
