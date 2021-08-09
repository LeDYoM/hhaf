#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/animation/animationcomponent.hpp>

namespace zoper
{

class Player : public GameBaseTile
{
public:
    using BoardTileData = GameBaseTile::BoardTileData;
    using BaseClass     = GameBaseTile;

    Player(htps::rptr<haf::scene::SceneNode> parent, htps::str name);
    ~Player() override;

    htps::PropertyState<htps::vector2dst> boardPosition;
    htps::PropertyState<Direction> currentDirection;

    bool canBeMoved(htps::vector2dst const& dest_position) const;

    void movePlayer(const Direction& direction);
    void launchAnimation(const htps::vector2df& toWhere);

    void tileAdded(const htps::vector2dst& position) override;
    void tileChanged(const htps::vector2dst& position,
                     const BoardTileData oldValue,
                     const BoardTileData newValue) override;

    void tileMoved(const htps::vector2dst& source,
                   const htps::vector2dst& dest) override;

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
