#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/include/ianimation.hpp>
#include <lib/scene_components/include/animationcomponent.hpp>

namespace zoper
{

namespace mtps = lib;
namespace haf = lib;
namespace scene = haf::scene;

class Player : public GameBaseTile
{
public:
    using BaseClass = GameBaseTile;

    Player(rptr<scene::SceneNode> parent, mtps::str name);
    ~Player() override;

    void configure(const mtps::vector2dst &bPosition,
                   const mtps::Rectf32 &box,
                   const mtps::vector2df &board2SceneFactor);

    PropertyState<mtps::vector2dst> boardPosition;
    PropertyState<Direction> currentDirection;

    void movePlayer(const Direction &direction);
    void launchAnimation(const mtps::vector2df &toWhere);

    void tileAdded(const mtps::vector2dst &position) override;
    void tileChanged(const mtps::vector2dst &position,
                     const board::BoardTileData oldValue,
                     const board::BoardTileData newValue) override;

    void tileMoved(const mtps::vector2dst &source,
                        const mtps::vector2dst &dest) override;

    void update() override;

private:
    void launchAnimationBack(const mtps::vector2df &toWhere);
    sptr<scene::AnimationComponent> animation_component_;
    scene::SceneNodeSPtr rotator_;
    scene::SceneNodeSPtr scalator_;
    vector2df m_board2SceneFactor;
};
} // namespace zoper

#endif
