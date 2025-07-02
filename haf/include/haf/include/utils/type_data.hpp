HTPS_PRAGMA_ONCE
#ifndef HAF_UTILS_TYPE_DATA_INCLUDE_HPP
#define HAF_UTILS_TYPE_DATA_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/types.hpp>
#include <compare>
#include <typeinfo>

namespace haf::utils
{
class type_index
{
public:
    type_index(std::type_info const& t_info) noexcept;

    [[nodiscard]] htps::size_type hash_code() const noexcept;
    [[nodiscard]] char const* name() const noexcept;
    [[nodiscard]] bool operator==(type_index const& rhs) const noexcept;
    [[nodiscard]] std::strong_ordering operator<=>(
        const type_index& rhs) const noexcept;

private:
    std::type_info const* t_info_;
};

template <typename T>
type_index type_of() noexcept
{
    return type_index{typeid(T)};
}

}  // namespace haf::utils

#endif
