#ifndef HAF_SCENE_HASNAME_HPP
#define HAF_SCENE_HASNAME_HPP

#include <htypes/include/str.hpp>

namespace haf::sys
{
class HasName
{
public:
    constexpr HasName(mtps::str const& name) noexcept : m_name(name) {}
    constexpr HasName(mtps::str&& name) noexcept : m_name(std::move(name)) {}
    constexpr HasName(HasName&& other) noexcept = default;
    constexpr HasName(const HasName& other)     = default;
    HasName& operator=(HasName&& other) noexcept = default;
    HasName& operator=(const HasName& other) = default;

    inline const mtps::str& name() const noexcept { return m_name; }

protected:
    ~HasName() {}

private:
    mtps::str m_name;
};
}  // namespace haf::sys

#endif
