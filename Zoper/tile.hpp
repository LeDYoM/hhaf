#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "lib/board/itilescontroller.hpp"
#include "lib/draw/renderizable.hpp"

namespace zoper
{
	class Tile : public lib::board::ITile, public lib::draw::Renderizable
	{
	public:
		explicit Tile(lib::board::BoardTileData data);
		Tile(const Tile &other) = delete;
		virtual ~Tile();
	};
}

#endif
