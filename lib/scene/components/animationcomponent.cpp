#include "animationcomponent.hpp"

#include <lib/scene/ianimation.hpp>
#include <lib/include/liblog.hpp>

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
                LockableVector<sptr<IAnimation>> m_animations;
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
                m_private->m_animations.update();

                for (auto animation : m_private->m_animations.current())
                {
                    if (!animation->animate()) 
                    {
                        animation->executeEndAction();
                        m_private->m_animations.remove_value(animation);
                    }
                }

                m_private->m_animations.update();
            }
		}
	}
}
