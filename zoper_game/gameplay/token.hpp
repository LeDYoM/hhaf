#pragma once

#ifndef ZOPER_TILE_HPP
#define ZOPER_TILE_HPP

#include "gamebasetile.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <lib/board/itile.hpp>
#include <lib/scene/components/animationcomponent.hpp>

namespace zoper
{
    using namespace lib;

    /**
    * This class represents one of the enemies in the board of the game.
    * 
    * The clas contains internal data like the token type inherited from
    * the base class. It also provides the required graphical information.
    */
    class Token : public GameBaseTile
    {
    public:
        Token(scene::SceneNode* const parent, str name, board::BoardTileData data, const Rectf32 &box);
        ~Token() override;

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
        sptr<scene::anim::AnimationComponent> animation_component_;
    };
}

#endif