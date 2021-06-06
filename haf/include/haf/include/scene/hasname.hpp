#ifndef HAF_SCENE_HASNAME_HPP
#define HAF_SCENE_HASNAME_HPP

#include <htypes/include/str.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::sys
{
class HAF_API HasName
{
public:
    constexpr HasName(htps::str const& name) noexcept : m_name(name) {}
    constexpr HasName(htps::str&& name) noexcept : m_name(std::move(name)) {}
    constexpr HasName(HasName&& other) noexcept = default;
    constexpr HasName(const HasName& other)     = default;
    HasName& operator=(HasName&& other) noexcept = default;
    HasName& operator=(const HasName& other) = default;

    inline const htps::str& name() const noexcept { return m_name; }

protected:
    ~HasName() {}

private:
    htps::str m_name;
};
}  // namespace haf::sys

#endif
