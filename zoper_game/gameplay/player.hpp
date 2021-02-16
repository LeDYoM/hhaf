#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>

namespace zoper
{

class Player : public GameBaseTile
{
public:
    using BaseClass = GameBaseTile;

    Player(mtps::rptr<haf::scene::SceneNode> parent, mtps::str name);
    ~Player() override;

    mtps::PropertyState<mtps::vector2dst> boardPosition;
    mtps::PropertyState<Direction> currentDirection;

    bool canBeMoved(mtps::vector2dst const& dest_position) const;

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
    mtps::u32 movements_{0U};
    mtps::size_type move_in_;
    mtps::size_type rotator_;
    mtps::size_type scalator_;
    mtps::size_type move_out_;
    void launchAnimationBack(const mtps::vector2df &toWhere);
    mtps::sptr<haf::scene::AnimationComponent> animation_component_;
    mtps::sptr<haf::scene::RenderizableSceneNode> render_scene_node_;
};
} // namespace zoper

#endif
