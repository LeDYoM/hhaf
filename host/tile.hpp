#ifndef ZOPER_TILE_HPP__
#define ZOPER_TILE_HPP__

#include "gamebasetile.hpp"

namespace zoper
{
	class Tile : public GameBaseTile
	{
	public:
		explicit Tile(lib::draw::SceneNode* const parent, lib::str name, lib::board::BoardTileData data, const lib::Rectf32 &box);
		virtual ~Tile();

		static void resetTileCounter();

	private:
		static lib::u32 m_tileCounter;
	};
}

#endif