#include "coloranimation.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			namespace anim
			{
				ColorAnimation::ColorAnimation(const s32 duration, sptr<Renderizable> node, const sf::Color &startColor, const sf::Color &endColor)
					: IValueAnimation(duration, node, startColor, endColor)
				{
				}


				ColorAnimation::~ColorAnimation()
				{
				}

				sf::Color interpolate(const sf::Color &color, float interpolateValue)
				{
					sf::Color value{ color };
					value.r = static_cast<lib::u8>(static_cast<float>(value.r) * interpolateValue);
					value.g = static_cast<lib::u8>(static_cast<float>(value.g) * interpolateValue);
					value.b = static_cast<lib::u8>(static_cast<float>(value.b) * interpolateValue);
					value.a = static_cast<lib::u8>(static_cast<float>(value.a) * interpolateValue);
					return value;
				}

				bool ColorAnimation::animate()
				{
					bool result = IAnimation::animate();
					sf::Color deltaColor{ _endValue - _startValue };
					sf::Color finalColor{ _startValue + (interpolate(deltaColor,_delta)) };
					_node->setColor(finalColor);
					return result;
				}

				sptr<ColorAnimation> ColorAnimation::create(const s32 duration, sptr<Renderizable> node, const sf::Color &startColor, const sf::Color &endColor)
				{
					auto animation = std::make_shared<ColorAnimation>(duration, node, startColor, endColor);
					return animation;
				}

				sptr<ColorAnimation> ColorAnimation::create(const s32 duration, sptr<Renderizable> node, const sf::Color &endColor)
				{
					auto animation = std::make_shared<ColorAnimation>(duration, node, endColor, endColor);
					return animation;
				}
			}
		}
	}
}
