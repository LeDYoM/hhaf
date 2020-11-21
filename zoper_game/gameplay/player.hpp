#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>

namespace zoper
{

class Player : public GameBaseTile
{
public:
    using BaseClass = GameBaseTile;

    Player(mtps::rptr<haf::scene::SceneNode> parent, mtps::str name);
    ~Player() override;

    void configure(const mtps::vector2dst &bPosition,
                   const mtps::Rectf32 &box,
                   const mtps::vector2df &board2SceneFactor);

    mtps::PropertyState<mtps::vector2dst> boardPosition;
    mtps::PropertyState<Direction> currentDirection;

    void movePlayer(const Direction &direction);
    void launchAnimation(const mtps::vector2df &toWhere);

    void tileAdded(const mtps::vector2dst &position) override;
    void tileChanged(const mtps::vector2dst &position,
                     const haf::board::BoardTileData oldValue,
                     const haf::board::BoardTileData newValue) override;

    void tileMoved(const mtps::vector2dst &source,
                        const mtps::vector2dst &dest) override;

    void update() override;

private:
    void launchAnimationBack(const mtps::vector2df &toWhere);
    mtps::sptr<haf::scene::AnimationComponent> animation_component_;
    haf::scene::SceneNodeSPtr rotator_scalator_;
    mtps::vector2df m_board2SceneFactor;
};
} // namespace zoper

#endif
