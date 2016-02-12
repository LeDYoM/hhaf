#include "gamebasetile.hpp"
#include <lib/core/log.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace zoper
{
	GameBaseTile::GameBaseTile(lib::board::BoardTileData data, const sf::Vector2f &size, const std::string &baseName) 
		: lib::board::ITile{ data }, lib::scn::draw::NodeShape(baseName,size,30)
	{
	}

	GameBaseTile::~GameBaseTile()
	{
	}

	sf::Color GameBaseTile::getColorForToken() const
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
		return c;
	}

}
