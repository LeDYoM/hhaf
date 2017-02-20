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
				vector_shared_pointers<IAnimation> m_animations;
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
				m_private->m_animations.emplace_back(std::move(nanimation));
			}

			void AnimationComponent::update()
			{
				if (!m_private->m_animations.empty()) {
					bool animsFinished{ false };
					for (auto& animation : m_private->m_animations) {
						if (!animation->animate()) {
							animation = nullptr;
							animsFinished = true;
						}
					}

					if (animsFinished) {
						m_private->m_animations.erase(std::remove(m_private->m_animations.begin(), m_private->m_animations.end(), nullptr), m_private->m_animations.end());
					}
				}
			}
		}
	}
}
