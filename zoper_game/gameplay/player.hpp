#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <haf/include/types/basic_types.hpp>
#include <haf/include/animation/animation_component.hpp>

namespace zoper
{

class Player : public GameBaseTile
{
    using BaseClass = GameBaseTile;

public:
    using BoardTileData     = BaseClass::BoardTileData;
    using BoardPositionType = BaseClass::BoardPositionType;

    Player(haf::types::rptr<haf::scene::SceneNode> parent,
           haf::types::str name);
    ~Player() override;

    htps::PropertyState<BoardPositionType> player_board_position;
    htps::PropertyState<Direction> currentDirection;

    bool canBeMovedTo(BoardPositionType const& dest_position) const override;

    void launchPlayerAnimation(htps::vector2df const& toWhere);

    void tileAdded() override;
    void tileChanged(BoardTileData const oldValue,
                     BoardTileData const newValue) override;

    void tileMoved(BoardPositionType const& source) override;

    void update() override;

private:
    htps::size_type move_in_;
    htps::size_type rotator_;
    htps::size_type scalator_;
    htps::size_type move_out_;
    void launchAnimationBack(haf::SceneCoordinates const& toWhere);
    haf::types::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif
