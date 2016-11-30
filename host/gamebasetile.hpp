#ifndef __GAMEBASETILE_HPP__
#define __GAMEBASETILE_HPP__

#include <lib/board/itilescontroller.hpp>
#include <lib/draw/nodeshape.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile, public lib::draw::NodeShape
	{
	public:
		explicit GameBaseTile(lib::board::BoardTileData data, const lib::vector2df &size, const std::string &baseName);
		GameBaseTile(const GameBaseTile &other) = delete;
		virtual ~GameBaseTile();

		lib::draw::Color getColorForToken() const;
	};
}

#endif
