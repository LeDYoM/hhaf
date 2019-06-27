#include "gamebasetile.hpp"

#include <lib/include/liblog.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::board;
	using namespace lib::scene;

	GameBaseTile::GameBaseTile(SceneNode* const parent, str name)
		: ITile{ }, SceneNode{ parent, std::move(name) }
	{
		data.setCallback([this]() { m_node->color = getColorForToken(); });
	}

    GameBaseTile::~GameBaseTile() = default;

	Color GameBaseTile::getColorForToken() const
	{
		switch (data.get())
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
			lib::log_debug_error("Error value for token: ", data.get(), " is not supported");
			return colors::White;
			break;
		}
	}
}