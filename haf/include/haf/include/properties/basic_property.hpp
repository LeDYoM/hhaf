HAF_PRAGMA_ONCE
#ifndef MTPS_BASIC_PROPERTY_INCLUDE_HPP
#define MTPS_BASIC_PROPERTY_INCLUDE_HPP

#include <haf/include/properties/iproperty.hpp>
#include <utility>

namespace haf::prop
{
template <typename T>
class BasicProperty : public IProperty<T>
{
public:
    using Base            = IProperty<T>;
    using value_type      = typename Base::value_type;
    using const_type      = typename Base::const_type;
    using reference       = typename Base::reference;
    using const_reference = typename Base::const_reference;
    using pointer         = typename Base::pointer;
    using const_pointer   = typename Base::const_pointer;

    constexpr BasicProperty() noexcept(std::is_default_constructible_v<T>) =
        default;

    constexpr BasicProperty(BasicProperty&&) noexcept(
        std::is_nothrow_move_constructible_v<T>) = default;
    BasicProperty(BasicProperty const&) noexcept(
        std::is_nothrow_copy_constructible_v<T>) = default;
    constexpr BasicProperty& operator            =(BasicProperty&&) noexcept(
        std::is_nothrow_move_assignable_v<T>) = default;
    constexpr BasicProperty& operator         =(BasicProperty const&) noexcept(
        std::is_nothrow_copy_assignable_v<T>) = default;

    constexpr BasicProperty(T&& iv) noexcept(
        std::is_nothrow_move_constructible_v<T>) :
        m_value{htps::move(iv)}
    {}
    constexpr BasicProperty(T const& iv) noexcept(
        std::is_nothrow_copy_constructible_v<T>) :
        m_value{iv}
    {}

    constexpr T const& operator()() const noexcept override { return m_value; }

    constexpr void operator=(T const& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>) override
    {
        m_value = v;
    }

    constexpr void operator=(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>) override
    {
        m_value = htps::move(v);
    }

protected:
    T m_value{};
};

}  // namespace haf::prop

#endif
