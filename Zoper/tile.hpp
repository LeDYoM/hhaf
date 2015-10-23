#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "lib/board/itilescontroller.hpp"

namespace zoper
{
	class Tile : public lib::board::ITile
	{
	public:
		Tile(lib::board::BoardTileData data);
		Tile(const Tile &other) = delete;
		virtual ~Tile();
	};
}

#endif
