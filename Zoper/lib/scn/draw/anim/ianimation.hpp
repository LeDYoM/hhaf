#ifndef __LIB_IANIMATION_HPP__
#define __LIB_IANIMATION_HPP__

#include "../renderizable.hpp"
#include "../../../log.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			namespace anim
			{
				class IAnimation
				{
				public:
					IAnimation(const s32 duration, sptr<Renderizable> node)
						: _duration{ duration }, _node{ node }
					{
						_clock.restart();
					}
					virtual const std::string animationType() const = 0;
					virtual bool animate()
					{
						currentTime = _clock.getElapsedTime().asMilliseconds();
						if (currentTime > _duration)
						{
							_delta = 1.0f;
							return false;
						}
						_delta = (static_cast<f32>(currentTime) / _duration);
						return true;
					}
					sptr<Renderizable> node() const { return _node; }
					virtual ~IAnimation(){}
				protected:
					s32 currentTime;
					s32 _duration;
					float _delta{ 0.0f };
					sptr<Renderizable> _node;
					sf::Clock _clock;
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
			}
		}
	}
}

#endif