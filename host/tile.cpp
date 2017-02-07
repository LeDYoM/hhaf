#include "tile.hpp"
#include <lib/draw/NodeShape.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(lib::board::BoardTileData data, const lib::Rectf32 &box) : GameBaseTile{ data, box, "tile" + std::to_string(_tileCounter) }
	{
		++_tileCounter;
//		color.set(getColorForToken());
	}

	Tile::~Tile() = default;

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}
