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
			AnimationComponent::AnimationComponent()
			{
				m_eventConnector.addSubscription(UpdateAnimationEvent::subscribe([](const events::Event&ev) {
					const auto &aEvent{ dynamic_cast<const UpdateAnimationEvent&>(ev) };
					const bool _continue{ aEvent.m_animation->animate() };
					if (_continue) {
						host().eventManager().resendCurrentEvent();
					}
				}));
			}

			AnimationComponent::~AnimationComponent() = default;

			void AnimationComponent::push_animation(sptr<IAnimation> nanimation, sptr<SceneNode> nodeTrack)
			{
				host().eventManager().addEvent(msptr<UpdateAnimationEvent>(std::move(nanimation),std::move(nodeTrack)));
			}
		}
	}
}
