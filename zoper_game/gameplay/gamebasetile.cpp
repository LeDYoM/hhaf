#include "gamebasetile.hpp"

#include <logger/include/log.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::board;
	using namespace lib::scene;

	GameBaseTile::GameBaseTile(SceneNode* const parent, str name, BoardTileData data)
		: ITile{ data }, SceneNode{ parent, std::move(name) }
	{
		setCallback([this]() {m_node->color = getColorForToken(); });
	}

	Color GameBaseTile::getColorForToken() const
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
			lib::log_debug_error("Error value for token: ", get(), " is not supported");
			return colors::White;
			break;
		}
	}
}