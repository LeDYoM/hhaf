#ifndef LIB_IANIMATION_INCLUDE_HPP__
#define LIB_IANIMATION_INCLUDE_HPP__

#include "renderizable.hpp"
#include <lib/core/timer.hpp>
#include <lib/include/types.hpp>
#include <lib/core/events/event.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			using animation_action_callback = std::function<void()>;
			static const animation_action_callback noAction;

			class IAnimation
			{
			public:
				IAnimation(const u64 duration, animation_action_callback &&onStart, animation_action_callback &&onEnd) noexcept
					: m_duration{ duration }, m_onStart{ std::move(onStart) }, m_onEnd{std::move(onEnd) }
				{
					m_timer.restart();
				}

				virtual bool animate()
				{
					m_currentTime = m_timer.getElapsedTime().asMilliSeconds();
					if (m_currentTime > m_duration) {
						m_delta = 1.0f;
						if (m_onEnd) m_onEnd();
						return false;
					}
					m_delta = (static_cast<f32>(m_currentTime) / m_duration);
					return true;
				}
				virtual ~IAnimation() = default;
			protected:
				u64 m_currentTime;
				u64 m_duration;
				f32 m_delta{ 0.0f };
				Timer m_timer;
				animation_action_callback m_onStart, m_onEnd;
			};

			template <typename T>
			class IPropertyAnimation : public IAnimation
			{
			public:
				IPropertyAnimation(const u64 duration, Property<T> &prop, T start, T end, 
					animation_action_callback onStart, animation_action_callback onEnd)
					: IAnimation{ duration, std::move(onStart),std::move(onEnd) },
					m_property{ prop }, m_startValue { std::move(start)	},
					m_endValue{ std::move(end) }, m_deltaValue{ m_endValue - m_startValue } {}

				virtual bool animate() override
				{
					const bool bResult{ IAnimation::animate() };
					m_property = T{ m_startValue + (m_deltaValue * m_delta) };
					return bResult;
				}

			protected:
				T m_startValue;
				T m_endValue;
				T m_deltaValue;
				Property<T> &m_property;
			};

			class UpdateAnimationEvent : public events::EventTemplate<UpdateAnimationEvent>
			{
			public:
				UpdateAnimationEvent(sptr<IAnimation> animation) : m_animation{ std::move(animation) } {}

				sptr<IAnimation> m_animation;
			};
		}
	}
}

#endif
