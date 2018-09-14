#pragma once

#ifndef ZOPER_TILE_HPP__
#define ZOPER_TILE_HPP__

#include "gamebasetile.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/board/itilescontroller.hpp>

namespace zoper
{
    using namespace lib;

	class Tile : public GameBaseTile
	{
	public:
		explicit Tile(scene::SceneNode* const parent, str name, board::BoardTileData data, const Rectf32 &box);
		virtual ~Tile();

		static void resetTileCounter();

        void tileAdded(const vector2dst &position) override;
        void tileRemoved(const vector2dst & /* position */) override;
        void tileChanged(const vector2dst & /*position */,
            const board::BoardTileData oldValue,
            const board::BoardTileData newValue) override;
        void tileMoved(const vector2dst& source,
            const vector2dst& dest) override;

	private:
		static u32 m_tileCounter;
	};
}

#endif