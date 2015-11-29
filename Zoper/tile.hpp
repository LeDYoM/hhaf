#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "gamebasetile.hpp"

namespace zoper
{
	class Tile : public GameBaseTile
	{
	public:
		explicit Tile(lib::board::BoardTileData data, const sf::Vector2f &size);
		Tile(const Tile &other) = delete;
		virtual ~Tile();

		static void resetTileCounter();
	private:
		static lib::u32 _tileCounter;
	};
}

#endif
