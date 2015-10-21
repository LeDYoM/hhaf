#ifndef __LIB_ITILESCONTROLLER_HPP__
#define __LIB_ITILESCONTROLLER_HPP__

#include "../types.hpp"
#include "../compileconfig.hpp"

namespace lib
{
	namespace board
	{
		class ITilesController
		{
		public:

			ITilesController() {}
			virtual ~ITilesController() {}

			virtual void tileSet(u32 x, u32 y, s32 oTile, s32 nTile) = 0;
			virtual void tileMoved(u32 xSource, u32 ySource, u32 xDest, u32 yDest, s32 tile) = 0;

		};
	}
}

#endif
