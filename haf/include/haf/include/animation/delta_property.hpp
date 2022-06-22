HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_DELTA_PROPERTY_INCLUDE_HPP
#define HAF_ANIMATION_DELTA_PROPERTY_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/properties/basic_property.hpp>
#include <htypes/include/properties/wrapper_property.hpp>
#include <haf/include/animation/idelta_property.hpp>
#include <haf/include/animation/animable_types.hpp>

namespace haf::anim
{
template <typename T>
class DeltaProperty : public IDeltaProperty
{
public:
    using Base            = IDeltaProperty;
    using value_type      = typename Base::value_type;
    using const_type      = typename Base::const_type;
    using reference       = typename Base::reference;
    using const_reference = typename Base::const_reference;
    using pointer         = typename Base::pointer;
    using const_pointer   = typename Base::const_pointer;

    constexpr DeltaProperty() = delete;

    constexpr DeltaProperty(htps::WrapperProperty<T> wrapper_property,
                            T const& start_value,
                            T const& end_value) :
        m_delta_property{0.0F},
        m_property{wrapper_property},
        m_start_value{start_value},
        m_end_value{end_value}
    {}

    constexpr htps::f32 const& operator()() const noexcept override
    {
        return m_delta_property();
    }

    constexpr void operator=(htps::f32 const& v) noexcept override
    {
        m_delta_property = v;
        updateDelta();
    }

    constexpr void operator=(htps::f32&& v) noexcept override
    {
        m_delta_property = htps::move(v);
        updateDelta();
    }

private:
    void updateDelta()
    {
        m_property =
            interpolate(m_start_value, m_end_value, m_delta_property());
    }

    htps::BasicProperty<htps::f32> m_delta_property;
    htps::WrapperProperty<T> m_property;
    T const m_start_value;
    T const m_end_value;
};

template <template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
htps::uptr<DeltaProperty<PropertyValue>> make_delta_property(
    ObjectType* const obj,
    PropertyType<PropertyValue>(ObjectType::*property_v),
    PropertyValue const& start_value,
    PropertyValue const& end_value)
{
    return htps::muptr<anim::DeltaProperty<PropertyValue>>(
        htps::WrapperProperty<PropertyValue>{obj, property_v}, start_value,
        end_value);
}

template <template <typename> typename PropertyType,
          typename PropertyValue,
          typename ObjectType>
htps::uptr<DeltaProperty<PropertyValue>> make_delta_property(
    PropertyType<PropertyValue>& property,
    PropertyValue const& start_value,
    PropertyValue const& end_value)
{
    return htps::muptr<anim::DeltaProperty<PropertyValue>>(
        htps::WrapperProperty<PropertyValue>{property}, start_value, end_value);
}

}  // namespace haf::anim

#endif
