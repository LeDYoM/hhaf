#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <boardmanager/include/boardmodel.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>

namespace zoper
{
using namespace lib;
class Player : public GameBaseTile
{
public:
    using BaseClass = GameBaseTile;

    Player(scene::SceneNode *const parent, str name);
    ~Player() override;

    void configure(const vector2dst &bPosition,
                   const Rectf32 &box,
                   const vector2df &board2SceneFactor);

    PropertyState<vector2dst> boardPosition;
    PropertyState<Direction> currentDirection;

    void movePlayer(const Direction &direction,
                    const sptr<board::BoardModelComponent> &boardModel);
    void launchAnimation(const vector2df &toWhere);

    void tileAdded(const vector2dst &position) override;
    void tileChanged(const vector2dst &position,
                     const board::BoardTileData oldValue,
                     const board::BoardTileData newValue) override;

    void update() override;

private:
    void launchAnimationBack(const vector2df &toWhere);
    sptr<scene::AnimationComponent> animation_component_;
    scene::SceneNodeSPtr rotator_;
    scene::SceneNodeSPtr scalator_;
    vector2df m_board2SceneFactor;
};
} // namespace zoper

#endif
