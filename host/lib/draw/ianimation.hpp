#ifndef __LIB_IANIMATION_HPP__
#define __LIB_IANIMATION_HPP__

#include "renderizable.hpp"
#include <lib/core/timer.hpp>
#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			using animation_action_callback = std::function<void()>;
			static const animation_action_callback noAction{};

			class IAnimation
			{
			public:
				IAnimation(const u32 duration, animation_action_callback &&onStart, animation_action_callback &&onEnd)
					: m_duration{ duration }, m_onStart{ std::move(onStart) }, m_onEnd{std::move(onEnd) }
				{
					_clock.restart();
				}
				virtual bool animate()
				{
					currentTime = _clock.getElapsedTime().asMilliSeconds();
					if (currentTime > m_duration)
					{
						_delta = 1.0f;
						if (m_onEnd) m_onEnd();
						return false;
					}
					_delta = (static_cast<f32>(currentTime) / m_duration);
					return true;
				}
				virtual ~IAnimation() = default;
			protected:
				u64 currentTime;
				u64 m_duration;
				float _delta{ 0.0f };
				Timer _clock;
				animation_action_callback m_onStart;
				animation_action_callback m_onEnd;
			};

			template <typename T>
			class IPropertyAnimation : public IAnimation
			{
			public:
				IPropertyAnimation(const s32 duration, Property<T> &prop, T start, T end, 
					animation_action_callback onStart, animation_action_callback onEnd)
					: IAnimation{ duration, std::move(onStart),std::move(onEnd) },
					m_property{ prop }, m_startValue { std::move(start)	},
					m_endValue{ std::move(end) }, m_deltaValue{ m_endValue - m_startValue } {}

				virtual bool animate() override
				{
					const bool bResult{ IAnimation::animate() };

					T finalValue{ m_startValue + (m_deltaValue * _delta) };
					m_property = finalValue;

					return bResult;
				}

			protected:
				T m_startValue;
				T m_endValue;
				T m_deltaValue;
				Property<T> &m_property;
			};

		}
	}
}

#endif
