#ifndef MTPS_PROPERTIES_INCLUDE_HPP
#define MTPS_PROPERTIES_INCLUDE_HPP

#include <type_traits>

#include "str_literal.hpp"

namespace htps
{
struct DummyTag
{};

/**
 * @brief Class provides a basic interface for properties. This is the base
 * class for any Property class.
 * @tparam T Inner type of the property.
 */
template <typename T, typename Tag>
class IProperty
{
public:
    using tag             = Tag;
    using value_type      = T;
    using const_type      = T const;
    using reference       = T&;
    using const_reference = T const&;
    using pointer         = T*;
    using const_pointer   = T const*;

    /**
     * @brief Get value of the property.
     * @return const T& The content of the property.
     */
    virtual const T& get() const noexcept = 0;

    /**
     * @brief Sets the vañue of the inner type of the property.
     *
     * @param v New value to set.
     * @return true The value has changed
     * @return false v was equal to the content, so no changes made.
     */
    virtual bool set(const T& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>)                              = 0;
    virtual bool set(T&& v) noexcept(std::is_nothrow_move_assignable_v<T>) = 0;
};

}  // namespace htps

namespace test_prop
{
template <str_literal_hash, typename T>
struct PropertyDataRead
{
    /**
     * @brief Get value of the property.
     * @return const T& The content of the property.
     */
    virtual const T& get() const noexcept = 0;

    virtual ~PropertyDataRead() = default;
};

template <str_literal_hash, typename T>
struct PropertyDataWrite
{
    /**
     * @brief Sets the vañue of the inner type of the property.
     *
     * @param v New value to set.
     * @return true The value has changed
     * @return false v was equal to the content, so no changes made.
     */
    virtual bool set(const T& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>)                              = 0;
    virtual bool set(T&& v) noexcept(std::is_nothrow_move_assignable_v<T>) = 0;

    virtual ~PropertyDataWrite() = default;
};

}  // namespace test_prop

#endif
