#ifndef ZOPER_TOKEN_HPP
#define ZOPER_TOKEN_HPP

#include "gamebasetile.hpp"

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>

#include <boardmanager/include/itile.hpp>
#include <haf/include/animation/animation_component.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>

namespace zoper
{
/**
 * @brief This class represents one of the enemies in the board of the game.
 * The clas contains internal data like the token type inherited from
 * the base class. It also provides the required graphical information.
 */
class Token : public GameBaseTile
{
    using BaseClass = GameBaseTile;
public:
    using BoardTileData = GameBaseTile::BoardTileData;
    using BoardPositionType = BaseClass::BoardPositionType;

    Token(htps::rptr<haf::scene::SceneNode> parent, htps::str name);
    ~Token() override;

    void onCreated() override;

    static void resetTileCounter();

    bool canBeMovedTo(BoardPositionType const& dest_position) const override;
    void tileAdded() override;
    void tileRemoved() override;
    void tileChanged(BoardTileData const oldValue,
                     BoardTileData const newValue) override;
    void tileMoved(BoardPositionType const& source) override;

private:
    void setTokenColor(haf::scene::Color const& token_color) override;

    static htps::u32 tile_counter_;
    fmath::vector2df board2SceneFactor_;
    htps::sptr<haf::anim::AnimationComponent> animation_component_;
    htps::sptr<haf::scene::RenderizableSceneNode> m_renderizable;
};
}  // namespace zoper

#endif