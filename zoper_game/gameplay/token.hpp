#pragma once

#ifndef ZOPER_TOKEN_HPP
#define ZOPER_TOKEN_HPP

#include "gamebasetile.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <boardmanager/include/itile.hpp>
#include <lib/scene_components/include/animationcomponent.hpp>

namespace zoper
{

class LevelProperties;

/// This class represents one of the enemies in the board of the game.
/// The clas contains internal data like the token type inherited from
/// the base class. It also provides the required graphical information.
class Token : public GameBaseTile
{
public:
    Token(mtps::rptr<haf::scene::SceneNode> parent, mtps::str name);
    ~Token() override;

    void configure(mtps::sptr<LevelProperties> level_properties,
                   haf::board::BoardTileData data,
                   const mtps::Rectf32 &box,
                   const mtps::vector2df &board2SceneFactor);

    static void resetTileCounter();

    void tileAdded(const mtps::vector2dst &position) override;
    void tileRemoved(const mtps::vector2dst & /* position */) override;
    void tileChanged(const mtps::vector2dst & /*position */,
                     const haf::board::BoardTileData oldValue,
                     const haf::board::BoardTileData newValue) override;
    void tileMoved(const mtps::vector2dst &source,
                   const mtps::vector2dst &dest) override;

private:
    static mtps::u32 m_tileCounter;
    mtps::vector2df board2SceneFactor_;
    mtps::sptr<haf::scene::AnimationComponent> animation_component_;
    mtps::sptr<LevelProperties> level_properties_;
};
} // namespace zoper

#endif