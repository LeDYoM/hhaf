#pragma once

#ifndef LIB_ANIMATION_COMPONENT_INCLUDE_HPP
#define LIB_ANIMATION_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/scene/components/icomponent.hpp>

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

    private:
        class AnimationComponentPrivate;
        uptr<AnimationComponentPrivate> m_private;
    };
}

#endif
