#include "tile.hpp"
#include "lib/scn/draw/ellipseshape.hpp"
#include <SFML/Graphics.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(lib::board::BoardTileData data, const sf::Vector2f &size) : GameBaseTile{ data, size, std::string("tile") + std::to_string(_tileCounter) }
	{
		sf::Color c;

		++_tileCounter;

		switch (getData())
		{
		case 0:
			c = sf::Color::Red;
			break;
		case 1:
			c = sf::Color::Green;
			break;
		case 2:
			c = sf::Color::Blue;
			break;
		case 3:
			c = sf::Color::Yellow;
			break;
		case 4:
			c = sf::Color::Magenta;
			break;
		default:
			c = sf::Color::White;
			LOG_ERROR("Error value for token: " << getData() << " is not supported");
			break;
		}
		auto this_ = getAsEllipseShape();
		this_->setFillColor(c);
		this_->setSize(size);
	}

	Tile::~Tile()
	{
	}

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}
