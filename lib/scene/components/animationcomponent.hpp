#pragma once

#ifndef LIB_ANIMATION_COMPONENT_INCLUDE_HPP
#define LIB_ANIMATION_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/datawrappers/timeview.hpp>

namespace lib::scene::anim
{
    class IAnimation;
    class AnimationComponent : public IComponent
    {
    public:
        AnimationComponent();
        ~AnimationComponent() override;

        virtual void update() override;
        void addAnimation(uptr<IAnimation>);

        template <typename PropertyType>
        void addPropertyAnimation(const TimePoint time,
        IProperty<PropertyType>& property, const PropertyType dest)
        {
            addAnimation(muptr<anim::IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<scene::Timer>(), time, property, property.get(), dest));
        }

        template <typename PropertyType>
        void addPropertyAnimation(const TimePoint time,
        IProperty<PropertyType>& property, const PropertyType start, const PropertyType dest)
        {
            addAnimation(muptr<anim::IPropertyAnimation<PropertyType>>(
            attachedNode()->dataWrapper<scene::Timer>(), time, property, start, dest));
        }

    private:
        class AnimationComponentPrivate;
        uptr<AnimationComponentPrivate> m_private;
    };
}

#endif
