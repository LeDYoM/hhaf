#pragma once

#ifndef LIB_ANIMATION_COMPONENT_INCLUDE_HPP
#define LIB_ANIMATION_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/icomponent.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/scene/include/ianimation.hpp>
#include <lib/scene/include/ipropertyanimation.hpp>

namespace lib::scene
{
class AnimationComponent : public IComponent
{
public:
    AnimationComponent();
    ~AnimationComponent() override;

    virtual void update() override;
    void addAnimation(uptr<IAnimation>);

    template <typename PropertyType>
    void addPropertyAnimation(const time::TimePoint time,
                              IProperty<PropertyType> &property,
                              const PropertyType dest,
                              IAnimation::ActionFunc endAction = {})
    {
        addAnimation(muptr<IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<time::Timer>(), time, property,
            property.get(), dest, std::move(endAction)));
    }

    template <typename PropertyType>
    void addPropertyAnimation(const time::TimePoint time,
                              IProperty<PropertyType> &property,
                              const PropertyType start,
                              const PropertyType dest,
                              IAnimation::ActionFunc endAction = {})
    {
        addAnimation(muptr<IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<time::Timer>(), time, property, start, dest, endAction));
    }

private:
    class AnimationComponentPrivate;
    uptr<AnimationComponentPrivate> m_private;
};
} // namespace lib::scene

#endif
