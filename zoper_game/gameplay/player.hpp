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
    using BoardTileData     = GameBaseTile::BoardTileData;
    using BoardPositionType = GameBaseTile::BoardPositionType;

    Player(haf::types::rptr<haf::scene::SceneNode> parent,
           haf::types::str name);
    ~Player() override;

    htps::PropertyState<BoardPositionType> boardPosition;
    htps::PropertyState<Direction> currentDirection;

    bool canBeMoved(BoardPositionType const& dest_position) const;

    void movePlayer(Direction const& direction);
    void launchPlayerAnimation(htps::vector2df const& toWhere);

    void tileAdded(BoardPositionType const& position) override;
    void tileChanged(BoardPositionType const& position,
                     BoardTileData const oldValue,
                     BoardTileData const newValue) override;

    void tileMoved(BoardPositionType const& source,
                   BoardPositionType const& dest) override;

    void update() override;

private:
    htps::u32 movements_{0U};
    htps::size_type move_in_;
    htps::size_type rotator_;
    htps::size_type scalator_;
    htps::size_type move_out_;
    void launchAnimationBack(const htps::vector2df& toWhere);
    haf::types::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif
