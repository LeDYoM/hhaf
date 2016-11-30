#include "gamebasetile.hpp"
#include <lib/core/log.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace zoper
{
	GameBaseTile::GameBaseTile(lib::board::BoardTileData data, const lib::vector2df &size, const std::string &baseName) 
		: lib::board::ITile{ data }, lib::draw::NodeShape(baseName,size,30)
	{
	}

	GameBaseTile::~GameBaseTile() = default;

	lib::draw::Color GameBaseTile::getColorForToken() const
	{
		switch (getData())
		{
		case 0:
			return lib::draw::colors::Red;
			break;
		case 1:
			return lib::draw::colors::Green;
			break;
		case 2:
			return lib::draw::colors::Blue;
			break;
		case 3:
			return lib::draw::colors::Yellow;
			break;
		case 4:
			return lib::draw::colors::Magenta;
			break;
		default:
			logError("Error value for token: ", getData(), " is not supported");
			return lib::draw::colors::White;
			break;
		}
	}

}
