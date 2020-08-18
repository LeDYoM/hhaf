#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"
#include "boardgroup.hpp"
#include <boardmanager/include/boardmanager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/scene_nodes/include/renderizable_scenenode.hpp>

namespace zoper
{
using namespace mtps;
using namespace haf;
using namespace haf::scene;
using namespace haf::time;

Player::Player(rptr<SceneNode> parent, str name) :
    BaseClass{std::move(parent), std::move(name)},
    boardPosition{},
    currentDirection{Direction{Direction::DirectionData::Up}},
    m_board2SceneFactor{}
{
    rotator_ = createSceneNode("player_rotator");

    auto render_scene_node = rotator_->createSceneNode<RenderizableSceneNode>(
        "player_render_scene_node");

    render_scene_node->buildNode(render_scene_node->renderizableBuilder()
                                     .name("player_render_scene_node")
                                     .figType(FigType_t::Shape)
                                     .pointCount(3U));
    node_     = render_scene_node->node();
    scalator_ = render_scene_node;
}

Player::~Player() = default;

void Player::configure(const vector2dst& bPosition,
                       const Rectf32& box,
                       const vector2df& board2SceneFactor)
{
    m_board2SceneFactor = board2SceneFactor;
    boardPosition.set(bPosition);
    node_->box.set(box);
}

void Player::update()
{
    BaseClass::update();

    if (boardPosition.readResetHasChanged())
    {
        DisplayLog::info("Player board position: ", boardPosition());
//        prop<Position>() = m_board2SceneFactor * boardPosition();
        DisplayLog::info("Player scene position: ", prop<Position>().get());
    }

    if (currentDirection.readResetHasChanged())
    {
        const auto direction{currentDirection()};

        const auto tileCenter{m_board2SceneFactor / 2.0F};
/*        rotator_->rotateAround(tileCenter, direction.angle());

        scalator_->scaleAround(
            tileCenter,
            (!direction.isVertical())
                ? vector2df{1.0F, 1.0F}
                : vector2df{m_board2SceneFactor.y / m_board2SceneFactor.x,
                            m_board2SceneFactor.x / m_board2SceneFactor.y});

        rotator_->prop<Position>() = tileCenter;
        scalator_->prop<Position>() = tileCenter;
*/
    }
}

void Player::movePlayer(const Direction& direction)
{
    LogAsserter::log_assert(direction.isValid(),
                            "Invalid direction passed to move");
    currentDirection = direction;
    auto nPosition   = direction.applyToVector(boardPosition());
    if (TokenZones::pointInCenter(nPosition))
    {
        getBoardModel()->moveTile(boardPosition(), nPosition);
    }
}

void Player::tileMoved(const vector2dst& /*source*/, const vector2dst& dest)
{
    boardPosition.set(dest);
}

void Player::launchAnimation(const vector2df& toWhere)
{
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep),
        prop<Position>(), prop<Position>()(), toWhere, Animation::AnimationDirection::Forward,
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
