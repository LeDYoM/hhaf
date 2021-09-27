#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/animation/animation_component.hpp>

namespace zoper
{

class Player : public GameBaseTile
{
   using BaseClass     = GameBaseTile;

public:
    using BoardTileData = GameBaseTile::BoardTileData;
   using BoardPosition_t = GameBaseTile::BoardPosition_t;
 
    Player(htps::rptr<haf::scene::SceneNode> parent, htps::str name);
    ~Player() override;

    htps::PropertyState<BoardPosition_t> boardPosition;
    htps::PropertyState<Direction> currentDirection;

    bool canBeMoved(BoardPosition_t const& dest_position) const;

    void movePlayer(Direction const& direction);
    void launchAnimation(htps::vector2df const& toWhere);

    void tileAdded(BoardPosition_t const& position) override;
    void tileChanged(BoardPosition_t const& position,
                     BoardTileData const oldValue,
                     BoardTileData const newValue) override;

    void tileMoved(BoardPosition_t const& source,
                   BoardPosition_t const& dest) override;

    void update() override;

private:
    htps::u32 movements_{0U};
    htps::size_type move_in_;
    htps::size_type rotator_;
    htps::size_type scalator_;
    htps::size_type move_out_;
    void launchAnimationBack(const htps::vector2df& toWhere);
    htps::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif
