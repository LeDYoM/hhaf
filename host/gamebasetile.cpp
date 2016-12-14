#include "gamebasetile.hpp"
#include <lib/core/log.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::board;
	using namespace lib::draw;

	GameBaseTile::GameBaseTile(BoardTileData data, const vector2df &size, const std::string &baseName)
		: ITile{ data }, NodeShape{baseName, size, 30} {}

	GameBaseTile::~GameBaseTile() = default;

	lib::draw::Color GameBaseTile::getColorForToken() const
	{
		switch (getData())
		{
		case 0:
			return colors::Red;
			break;
		case 1:
			return colors::Green;
			break;
		case 2:
			return colors::Blue;
			break;
		case 3:
			return colors::Yellow;
			break;
		case 4:
			return colors::Magenta;
			break;
		default:
			logError("Error value for token: ", getData(), " is not supported");
			return colors::White;
			break;
		}
	}

}
