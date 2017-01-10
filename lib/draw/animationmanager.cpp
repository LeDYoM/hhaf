#include "animationmanager.hpp"

#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			AnimationManager::AnimationManager() = default;
			AnimationManager::~AnimationManager() = default;

			void AnimationManager::addAnimation(sptr<IAnimation> nanimation)
			{
//				m_animations.push_back(nanimation);

				m_eventConnector.addSubscription(UpdateAnimationEvent::subscribe([this](const events::Event&ev) {
					const auto &aEvent{ dynamic_cast<const UpdateAnimationEvent&>(ev) };
					const bool _continue{ aEvent.m_animation->animate() };
					if (_continue) {
						host().eventManager().postEvent(aEvent);
					}
				}));

			}

			void AnimationManager::updateAnimations()
			{
				if (!m_animations.empty()) {
					for (auto &animation : m_animations) {
						if (!animation->animate()) {
							m_animationsToDelete.push_back(animation);
						}
					}

					if (!m_animationsToDelete.empty()) {
						for (auto animation : m_animationsToDelete) {
							removespFrom(m_animations, animation);
						}
						m_animationsToDelete.clear();
					}
				}
			}
		}
	}
}
