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
			class IAnimation
			{
			public:
				IAnimation(const u32 duration, sptr<Renderizable> node)
					: _duration{ duration }, _node{ node }
				{
					_clock.restart();
				}
				virtual const std::string animationType() const { return ""; }
				virtual bool animate()
				{
					currentTime = _clock.getElapsedTime().asMilliSeconds();
					if (currentTime > _duration)
					{
						_delta = 1.0f;
						return false;
					}
					_delta = (static_cast<f32>(currentTime) / _duration);
					return true;
				}
				sptr<Renderizable> node() const { return _node; }
				virtual ~IAnimation() = default;
			protected:
				u64 currentTime;
				u64 _duration;
				float _delta{ 0.0f };
				sptr<Renderizable> _node;
				Timer _clock;
			};

			template <typename T>
			class IValueAnimation : public IAnimation
			{
			public:
				IValueAnimation(const s32 duration, sptr<Renderizable> node, const T&start, const T&end)
					: IAnimation(duration, node), _startValue(start), _endValue(end) {}

			protected:
				T _startValue;
				T _endValue;
			};

			template <typename T>
			class IPropertyAnimation : public IAnimation
			{
			public:
				IPropertyAnimation(const s32 duration, Property<T> &prop, T start, T end)
					: IAnimation(duration, nullptr), 
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
