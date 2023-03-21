HTPS_PRAGMA_ONCE
#ifndef HTPS_IPROPERTY_INCLUDE_HPP
#define HTPS_IPROPERTy_INCLUDE_HPP

#include <type_traits>

namespace haf::prop
{
/**
 * @brief Class provides a basic interface for properties. This is the base
 * class for any Property class.
 * @tparam T Inner type of the property.
 */
template <typename T>
class IProperty
{
public:
    using value_type      = T;
    using const_type      = T const;
    using reference       = T&;
    using const_reference = T const&;
    using pointer         = T*;
    using const_pointer   = T const*;

    virtual void operator                     =(T const& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>) = 0;
    virtual void operator                     =(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>) = 0;

    virtual T const& operator()() const noexcept = 0;
};

}  // namespace haf::prop

#endif
