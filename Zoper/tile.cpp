#include "tile.hpp"
#include "lib/scn/draw/ellipseshape.hpp"
#include <SFML/Graphics.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(lib::board::BoardTileData data, const sf::Vector2f &size) : GameBaseTile{ data, size, std::string("tile") + std::to_string(_tileCounter) }
	{
		++_tileCounter;
		auto this_ = getAsEllipseShape();
		this_->setFillColor(getColorForToken());
	}

	Tile::~Tile()
	{
	}

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}
