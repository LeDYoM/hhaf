HAF_PRAGMA_ONCE
#ifndef HTPS_WRAPPER_PROPERTY_INCLUDE_HPP
#define HTPS_WRAPPER_PROPERTY_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty.hpp>
#include <utility>

namespace haf::prop
{
template <typename T>
class WrapperProperty : public IProperty<T>
{
public:
    using Base            = IProperty<T>;
    using value_type      = typename Base::value_type;
    using const_type      = typename Base::const_type;
    using reference       = typename Base::reference;
    using const_reference = typename Base::const_reference;
    using pointer         = typename Base::pointer;
    using const_pointer   = typename Base::const_pointer;

    template <template <typename> typename PropertyType,
              typename PropertyValue,
              typename ObjectType>
    constexpr WrapperProperty(
        ObjectType* const obj,
        PropertyType<PropertyValue>(ObjectType::* property_v)) :
        m_property{&(obj->*property_v)}
    {}

    constexpr T const& operator()() const noexcept override
    {
        return (*m_property)();
    }

    constexpr void operator=(T const& v) noexcept(
        std::is_nothrow_copy_assignable_v<T>) override
    {
        (*m_property) = v;
    }

    constexpr void operator=(T&& v) noexcept(
        std::is_nothrow_move_assignable_v<T>) override
    {
        (*m_property) = core::move(v);
    }

protected:
    core::rptr<IProperty<T>> m_property;
};

}  // namespace haf::prop

#endif
