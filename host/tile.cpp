#include "tile.hpp"
#include <lib/draw/NodeShape.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(std::string name, SceneNode *parent, lib::board::BoardTileData data, const lib::Rectf32 &box) : 
		GameBaseTile{ name + std::to_string(_tileCounter) + std::to_string(_tileCounter), parent, data, box, }
	{
		++_tileCounter;
		setColor(getColorForToken());
	}

	Tile::~Tile() = default;

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}
