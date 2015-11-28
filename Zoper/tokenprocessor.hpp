#ifndef __TOKENPROCESSOR_HPP__
#define __TOKENPROCESSOR_HPP__

#include "direction.hpp"
#include "lib/board/boardmodel.hpp"
#include <functional>

namespace zoper
{
	class TokenProcessor
	{
	public:
		void operator()(const Direction &loopDirection, const lib::vector2du32 &_loopPosition, lib::board::BoardModel &r_boardModel,
			std::function<bool(const lib::vector2du32 &)> stayCondition,
			std::function<void(lib::board::BoardModel &r_boardModel, const Direction &,const lib::vector2du32 &)> action)
		{
			lib::vector2du32 loopPosition{ _loopPosition };
			// Now, we have the data for the new token generated, but first, lets start to move the row or col.
			bool stay;
			do
			{
				// The position of the current token is the current position + the direction of the token zone
				// Exit loop condition: did we arrive to the center or is any of the positions invalid?
				stay = r_boardModel.validCoords(loopDirection.negate().applyToVector(loopPosition));
				if (stay)
				{
					// Move the token
					action(r_boardModel,loopDirection, loopPosition);
//					r_boardModel.moveTile(loopPosition, loopDirection.negate().applyToVector(loopPosition));
				}
				// The next token to move is in the opossite direction that we moved
				loopPosition = loopDirection.applyToVector(loopPosition);
				stay = r_boardModel.validCoords(loopPosition) && stayCondition(loopPosition);

			} while (stay);
		}
	};
}

#endif
