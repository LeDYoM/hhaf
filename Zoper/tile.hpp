#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "lib/board/itilescontroller.hpp"
#include "lib/scn/renderizable.hpp"

namespace zoper
{
	class Tile : public lib::board::ITile, public lib::scn::Renderizable
	{
	public:
		explicit Tile(lib::board::BoardTileData data,lib::u32 index);
		Tile(const Tile &other) = delete;
		virtual ~Tile();
	};
}

#endif
