#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"
#include "boardgroup.hpp"
#include <boardmanager/include/boardmanager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene_nodes/renderizable_scenenode.hpp>

namespace zoper
{
using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::time;

Player::Player(rptr<SceneNode> parent, str name) :
    BaseClass{std::move(parent), std::move(name)},
    boardPosition{},
    currentDirection{Direction{Direction::DirectionData::Up}}
{
    render_scene_node_ =
        createSceneNode<RenderizableSceneNode>("player_render_scene_node");

    render_scene_node_->buildNode(render_scene_node_->renderizableBuilder()
                                      .name("player_render_scene_node")
                                      .figType(FigType_t::Shape)
                                      .pointCount(3U));
    node_     = render_scene_node_->node();
    move_in_  = render_scene_node_->addTransformation();
    rotator_  = render_scene_node_->addTransformation();
    scalator_ = render_scene_node_->addTransformation();
    move_out_ = render_scene_node_->addTransformation();
    node_->box.set(rectFromSize(board2Scene({1, 1})));

}

Player::~Player() = default;

void Player::update()
{
    BaseClass::update();

    if (boardPosition.readResetHasChanged())
    {
        DisplayLog::info("Player board position: ", boardPosition());
        prop<Position>() = board2Scene(boardPosition());
        DisplayLog::info("Player scene position: ", prop<Position>().get());
    }

    if (currentDirection.readResetHasChanged())
    {
        const auto direction{currentDirection()};

        const auto tileCenter{board2SceneFactor() / 2.0F};
        render_scene_node_->getTransformation(move_in_).prop<Position>() =
            tileCenter;

        render_scene_node_->getTransformation(rotator_).prop<Rotation>().set(
            direction.angle());

        render_scene_node_->getTransformation(scalator_).prop<Scale>().set(
            (direction.isVertical())
                ? vector2df{board2SceneFactor().y / board2SceneFactor().x,
                            board2SceneFactor().x / board2SceneFactor().y}
                : vector2df{1.0F, 1.0F});

        render_scene_node_->getTransformation(move_out_).prop<Position>() =
            -tileCenter;
    }
}

bool Player::canBeMoved(htps::vector2dst const& dest_position) const
{
    return TokenZones::pointInCenter(dest_position);
}

void Player::movePlayer(const Direction& direction)
{
    LogAsserter::log_assert(direction.isValid(),
                            "Invalid direction passed to move");
    currentDirection = direction;
    auto nPosition   = direction.applyToVector(boardPosition());
    auto result      = getBoardManager()->moveTile(boardPosition(), nPosition);
    if (result)
    {
        ++movements_;
    }
}

void Player::tileMoved(const vector2dst& source, const vector2dst& dest)
{
    BaseClass::tileMoved(source, dest);
    DisplayLog::info("Player board position: ", dest);
    prop<Position>() = board2Scene(dest);
    DisplayLog::info("Player scene position: ", prop<Position>().get());

    boardPosition.set(dest);
}

void Player::launchAnimation(const vector2df& toWhere)
{
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep),
        prop<Position>(), prop<Position>()(), toWhere,
        Animation::AnimationDirection::Forward,
        [this, currentPosition = prop<Position>()()]() {
            launchAnimationBack(currentPosition);
        });
}

void Player::launchAnimationBack(const vector2df& toWhere)
{
    DisplayLog::info("Creating animation for player to go back");
    currentDirection = currentDirection().negate();
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep),
        prop<Position>(), prop<Position>().get(), toWhere);
}

void Player::tileAdded(const vector2dst& position_)
{
    DisplayLog::info("TokenPlayer appeared at ", position_);
    node_->color.set(getColorForToken());

    // Set the position in the scene depending on the board position
    boardPosition.set(position_);
}

void Player::tileChanged(const vector2dst& position_,
                         const board::BoardTileData oldValue,
                         const board::BoardTileData newValue)
{
    BaseClass::tileChanged(position_, oldValue, newValue);
    DisplayLog::info("Player (position ", position_, ") changed from ",
                     oldValue, " to ", newValue);
}

}  // namespace zoper
