#ifndef __GAMEBASETILE_HPP__
#define __GAMEBASETILE_HPP__

#include <lib/board/itilescontroller.hpp>
#include <lib/draw/nodeshape.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile, public lib::scn::draw::NodeShape
	{
	public:
		explicit GameBaseTile(lib::board::BoardTileData data, const sf::Vector2f &size, const std::string &baseName);
		GameBaseTile(const GameBaseTile &other) = delete;
		virtual ~GameBaseTile();

		sf::Color getColorForToken() const;
	};
}

#endif
