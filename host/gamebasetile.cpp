#include "gamebasetile.hpp"
#include <lib/core/log.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::board;
	using namespace lib::draw;

	GameBaseTile::GameBaseTile(BoardTileData data, const vector2df &size, const std::string &baseName, const u32 pointCount)
		: ITile{ data }, NodeShape{baseName, size, nullptr, pointCount, colors::White} {}

	lib::draw::Color GameBaseTile::getColorForToken() const
	{
		switch (get())
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
			logError("Error value for token: ", get(), " is not supported");
			return colors::White;
			break;
		}
	}

}
