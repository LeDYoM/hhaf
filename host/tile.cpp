#include "tile.hpp"
#include <lib/draw/nodes/nodeshape.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(SceneNode *parent, std::string name, lib::board::BoardTileData data, const lib::Rectf32 &box) :
		GameBaseTile{ parent, name + std::to_string(_tileCounter) + std::to_string(_tileCounter), data, box, }
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
