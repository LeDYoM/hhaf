#include "tile.hpp"
#include "lib/scn/draw/ellipseshape.hpp"
#include <SFML/Graphics.hpp>

namespace zoper
{
	Tile::Tile(lib::board::BoardTileData data, lib::u32 index) : lib::board::ITile{ data }, lib::scn::draw::Renderizable("",new lib::scn::draw::EllipseShape)
	{
		sf::Color c;
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
//		this_->setPointCount(5);

	}

	Tile::~Tile()
	{
	}
}
