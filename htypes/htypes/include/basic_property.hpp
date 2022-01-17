#ifndef MTPS_BASIC_PROPERTY_INCLUDE_HPP
#define MTPS_BASIC_PROPERTY_INCLUDE_HPP

#include "properties.hpp"
#include <utility>

namespace htps
{
template <typename T, typename Tag = DummyTag>
class BasicProperty : public IProperty<T, Tag>
{
public:
    using Base            = IProperty<T, Tag>;
    using tag             = typename Base::tag;
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
    BasicProperty(const BasicProperty&) noexcept(
        std::is_nothrow_copy_constructible_v<T>) = default;
    constexpr BasicProperty& operator            =(BasicProperty&&) noexcept(
        std::is_nothrow_move_assignable_v<T>) = default;
    constexpr BasicProperty& operator         =(BasicProperty const&) noexcept(
        std::is_nothrow_copy_assignable_v<T>) = default;

    constexpr BasicProperty(T&& iv) noexcept(
        std::is_nothrow_move_constructible_v<T>) :
        value_{std::move(iv)}
    {}
    constexpr BasicProperty(const T& iv) noexcept(
        std::is_nothrow_copy_constructible_v<T>) :
        value_{iv}
    {}

    constexpr const T& operator()() const noexcept { return value_; }
    constexpr void operator=(const T& v) { set(v); }

    constexpr void operator=(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>)
    {
        set(std::move(v));
    }

    constexpr const T& get() const noexcept override final { return value_; }
    inline bool set(const T& v) noexcept(noexcept(Base::set(v))) override
    {
        if (!(value_ == v))
        {
            value_ = v;
            return true;
        }
        return false;
    }

    inline bool set(T&& v) noexcept(noexcept(Base::set(std::move(v)))) override
    {
        if (!(value_ == std::forward<T>(v)))
        {
            value_ = std::move(v);
            return true;
        }
        return false;
    }

protected:
    T value_{};
};
}  // namespace htps

#endif
