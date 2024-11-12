#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_component.hpp>

namespace zoper
{

class Player : public GameBaseTile
{
    using BaseClass = GameBaseTile;

public:
    using BoardTileData     = BaseClass::BoardTileData;
    using BoardPositionType = BaseClass::BoardPositionType;

    Player(htps::rptr<haf::scene::SceneNode> parent,
           htps::str name);
    ~Player() override;

    haf::prop::PropertyState<BoardPositionType> player_board_position;
    haf::prop::PropertyState<Direction> currentDirection;

    bool canBeMovedTo(BoardPositionType const& dest_position) const override;

    void launchPlayerAnimation(fmath::vector2df const& toWhere);

    void tileAdded() override;
    void tileChanged(BoardTileData const oldValue,
                     BoardTileData const newValue) override;

    void tileMoved(BoardPositionType const& source) override;

    void update() override;

private:
    void setTokenColor(haf::scene::Color const& token_color) override;

    htps::sptr<haf::scene::RenderizableSceneNode> m_renderizable_scene_node;
    void launchAnimationBack(haf::SceneCoordinates const& toWhere);
    htps::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif
