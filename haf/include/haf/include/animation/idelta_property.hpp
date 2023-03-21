HTPS_PRAGMA_ONCE
#ifndef HAF_ANIMATION_IDELTA_PROPERTY_INCLUDE_HPP
#define HAF_ANIMATION_IDELTA_PROPERTY_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/properties/iproperty.hpp>

namespace haf::anim
{
class IDeltaProperty : public prop::IProperty<htps::f32>
{
public:
    using Base            = prop::IProperty<htps::f32>;
    using value_type      = typename Base::value_type;
    using const_type      = typename Base::const_type;
    using reference       = typename Base::reference;
    using const_reference = typename Base::const_reference;
    using pointer         = typename Base::pointer;
    using const_pointer   = typename Base::const_pointer;

    using Base::operator();
    using Base::operator=;

    virtual ~IDeltaProperty() = default;
};
}  // namespace haf::anim

#endif
