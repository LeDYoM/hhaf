#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "gamebasetile.hpp"

namespace zoper
{
	class Tile : public GameBaseTile
	{
	public:
		explicit Tile(lib::draw::SceneNode* const parent, lib::str_const &&name, lib::board::BoardTileData data, const lib::Rectf32 &box);
		virtual ~Tile();

		static void resetTileCounter();

	private:
		static lib::u32 _tileCounter;
	};
}

#endif