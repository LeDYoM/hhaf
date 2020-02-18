#pragma once

#ifndef LIB_ANIMATION_COMPONENT_INCLUDE_HPP
#define LIB_ANIMATION_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/icomponent.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/scene/ianimation.hpp>

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
        void addPropertyAnimation(const TimePoint time,
            IProperty<PropertyType>& property,
            const PropertyType dest,
            ActionFunc endAction = {})
        {
            addAnimation(muptr<IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<scene::Timer>(), time, property, 
            property.get(), dest, std::move(endAction)));
        }

        template <typename PropertyType>
        void addPropertyAnimation(const TimePoint time,
            IProperty<PropertyType>& property, 
            const PropertyType start,
            const PropertyType dest,
            ActionFunc endAction = {})
        {
            addAnimation(muptr<IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<scene::Timer>(), time, property, start, dest, endAction));
        }

    private:
        class AnimationComponentPrivate;
        uptr<AnimationComponentPrivate> m_private;
    };
}

#endif
