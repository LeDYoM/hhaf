#ifndef HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP
#define HAF_ANIMATION_PROPERTY_ANIMATION_DATA_INCLUDE_HPP

#include <htypes/include/properties.hpp>

namespace haf::anim
{
template <typename T, typename PropertyTag>
class PropertyAnimationData
{
public:
    htps::IProperty<T, PropertyTag>* property_;
    T startValue_;
    T endValue_;
};

}  // namespace haf::anim

#endif
