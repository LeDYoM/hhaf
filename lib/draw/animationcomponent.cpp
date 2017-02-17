#include "animationcomponent.hpp"
#include "ianimation.hpp"

#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			class AnimationComponent::AnimationComponentPrivate
			{
			public:
				AnimationComponentPrivate() {}
				vector_unique_pointers<IAnimation> m_animations;
			};
			AnimationComponent::AnimationComponent()
				: m_private{ new AnimationComponentPrivate }
			{
			}

			AnimationComponent::~AnimationComponent()
			{
				__ASSERT(m_private, "Destructing private class that is nullptr");
				delete m_private;
			}

			void AnimationComponent::addAnimation(uptr<IAnimation> nanimation)
			{
				m_private->m_animations.push_back(std::move(nanimation));
			}

			void AnimationComponent::update()
			{
				for (auto& animation : m_private->m_animations)
				{
					animation->animate();
				}
			}
		}
	}
}
