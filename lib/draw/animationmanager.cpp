#include "animationmanager.hpp"
#include "ianimation.hpp"
#include "idrawable.hpp"

#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			AnimationManager::AnimationManager()
			{
				m_eventConnector.addSubscription(UpdateAnimationEvent::subscribe([](const events::Event&ev) {
					const auto &aEvent{ dynamic_cast<const UpdateAnimationEvent&>(ev) };
					const bool _continue{ aEvent.m_animation->animate() };
					if (_continue) {
						host().eventManager().resendCurrentEvent();
					}
				}));
			}

			AnimationManager::~AnimationManager() = default;

			void AnimationManager::push_animation(sptr<IAnimation> nanimation, sptr<IDrawable> nodeTrack)
			{
				host().eventManager().addEvent(msptr<UpdateAnimationEvent>(std::move(nanimation),std::move(nodeTrack)));
			}
		}
	}
}
