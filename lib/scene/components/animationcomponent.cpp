#include "animationcomponent.hpp"
#include <lib/scene/ianimation.hpp>

#include <mtypes/include/log.hpp>
#include <mtypes/include/lockablevector.hpp>

namespace lib
{
	namespace scene
	{
		namespace anim
		{
			class AnimationComponent::AnimationComponentPrivate
			{
			public:
				AnimationComponentPrivate() {}
                LockableVector<IAnimation> m_animations;
			};
			AnimationComponent::AnimationComponent()
				: m_private{ muptr<AnimationComponentPrivate>() } {}

			AnimationComponent::~AnimationComponent() {}

			void AnimationComponent::addAnimation(uptr<IAnimation> nanimation)
			{
				m_private->m_animations.push_back(std::move(nanimation));
			}

			void AnimationComponent::update()
			{
                m_private->m_animations.update([](auto animation) {
                    if (!animation->animate()) {
                        animation->executeEndAction();
                        return false;
                    }
                    return true;
                });
			}
		}
	}
}
