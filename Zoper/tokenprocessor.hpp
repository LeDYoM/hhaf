#ifndef __TOKENPROCESSOR_HPP__
#define __TOKENPROCESSOR_HPP__

#include "direction.hpp"
#include "lib/board/boardmodel.hpp"

namespace zoper
{
	class TokenProcessor
	{
	public:
		TokenProcessor() {}
		virtual ~TokenProcessor() {}

		virtual void updateDestPosition(const Direction &direction)
		{
			// The position of the current token is the current position + the direction of the token zone
			destPosition = direction.applyToVector(loopPosition);
		}

		virtual void action(const lib::vector2du32 &loopPosition, const lib::vector2du32 &destPosition)
		{
			p_boardModel->moveTile(loopPosition, destPosition, true);
		}
		virtual bool update(const Direction &direction)
		{
			updateDestPosition(direction);
			// Exit loop condition: did we arrive to the center or is any of the positions invalid?
			bool stay = /*!pointInCenter(loopPosition) &&*/ p_boardModel->validCoords(loopPosition) && p_boardModel->validCoords(destPosition);
			if (stay)
			{
				// Move the token
				action(loopPosition, destPosition);
				p_boardModel->moveTile(loopPosition, destPosition, true);
			}
			// The next token to move is in the opossite direction that we moved
			loopPosition = direction.negate().applyToVector(loopPosition);
		}
		lib::vector2du32 loopPosition;
		lib::vector2du32 destPosition;
		lib::board::BoardModel *p_boardModel;
	};
}

#endif
