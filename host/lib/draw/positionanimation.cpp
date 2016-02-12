#include "positionanimation.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			namespace anim
			{
				PositionAnimation::PositionAnimation(const s32 duration, sptr<Renderizable> node, const vector2df &startPosition, const vector2df &endPosition)
					: IValueAnimation(duration,node,startPosition,endPosition)
				{
				}


				PositionAnimation::~PositionAnimation()
				{
				}

				bool PositionAnimation::animate()
				{
					bool result = IAnimation::animate();
					vector2df deltaPosition{ _endValue - _startValue };
					vector2df finalPosition{ _startValue + (deltaPosition*_delta) };
					_node->setPosition(finalPosition);
					return result;
				}

				sptr<PositionAnimation> PositionAnimation::create(const s32 duration, sptr<Renderizable> node, const vector2df &startPosition, const vector2df &endPosition)
				{
					auto animation = std::make_shared<PositionAnimation>(duration, node, startPosition, endPosition);
					return animation;
				}

				sptr<PositionAnimation> PositionAnimation::create(const s32 duration, sptr<Renderizable> node, const vector2df &endPosition)
				{
					auto animation = std::make_shared<PositionAnimation>(duration, node, node->getPosition(), endPosition);
					return animation;
				}
			}
		}
	}
}
