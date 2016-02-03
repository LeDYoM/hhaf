#include "tile.hpp"
#include <lib/draw/NodeShape.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(lib::board::BoardTileData data, const sf::Vector2f &size) : GameBaseTile{ data, size, std::string("tile") + std::to_string(_tileCounter) }
	{
		++_tileCounter;
		setColor(getColorForToken());
	}

	Tile::~Tile()
	{
	}

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}
