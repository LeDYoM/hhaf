#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"
#include "boardgroup.hpp"
#include <boardmanager/include/boardmodel.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/scenenodetypes.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;

Player::Player(rptr<SceneNode> parent, str name)
    : BaseClass{std::move(parent), std::move(name)},
      boardPosition{},
      currentDirection{Direction{Direction::DirectionData::Up}},
      m_board2SceneFactor{}
{
    rotator_ = createSceneNode("player_rotator");

    auto render_scene_node = rotator_->createSceneNode<RenderizableSceneNode>(
        "player_render_scene_node", FigType_t::Shape, 3U);

    m_node = render_scene_node->node();
    scalator_ = render_scene_node;
    data.set(0);
}

Player::~Player() {}

void Player::configure(const vector2dst &bPosition,
                       const Rectf32 &box, const vector2df &board2SceneFactor)
{
    m_board2SceneFactor = board2SceneFactor;
    boardPosition.set(bPosition);
    m_node->box.set(box);
}

void Player::update()
{
    BaseClass::update();

    if (boardPosition.readResetHasChanged())
    {
        DisplayLog::info("Player board position: ", boardPosition());
        position = m_board2SceneFactor * boardPosition();
        DisplayLog::info("Player scene position: ", position());
    }

    if (currentDirection.readResetHasChanged())
    {
        const auto direction{currentDirection()};

        const auto tileCenter{m_board2SceneFactor / 2.0F};
        rotator_->rotateAround(tileCenter, direction.angle());

        scalator_->scaleAround(
            tileCenter,
            (!direction.isVertical())
                ? vector2df{1.0F, 1.0F}
                : vector2df{
                      m_board2SceneFactor.y / m_board2SceneFactor.x,
                      m_board2SceneFactor.x / m_board2SceneFactor.y});
    }
}

auto getBoardModel(Player& player)
{
    auto board_group{player.ancestor<BoardGroup>()};
    log_assert(board_group != nullptr, "Invalid BoardModel received");

    return board_group != nullptr ?
        board_group->boardModel() : nullptr;
}

void Player::movePlayer(const Direction &direction)
{
    log_assert(direction.isValid(), "Invalid direction passed to move");
    currentDirection = direction;
    auto nPosition = direction.applyToVector(boardPosition());
    if (TokenZones::pointInCenter(nPosition))
    {
        getBoardModel(*this)->moveTile(boardPosition(), nPosition);
    }
}

void Player::tileMoved(const vector2dst &/*source*/, const vector2dst &dest)
{
    boardPosition.set(dest);
}

void Player::launchAnimation(const vector2df &toWhere)
{
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(gameplay::constants::MillisAnimationLaunchPlayerStep),
        position,
        toWhere,
        [this, currentPosition = position()]() { launchAnimationBack(currentPosition); });
}

void Player::launchAnimationBack(const vector2df &toWhere)
{
    DisplayLog::info("Creating animation for player to go back");
    currentDirection = currentDirection().negate();
    ensureComponentOfType(animation_component_);
    animation_component_->addPropertyAnimation(
        TimePoint_as_miliseconds(gameplay::constants::MillisAnimationLaunchPlayerStep),
        position, toWhere);
}

void Player::tileAdded(const vector2dst &position_)
{
    DisplayLog::info("TokenPlayer appeared at ", position_);
    m_node->color.set(getColorForToken());

    // Set the position in the scene depending on the board position
    boardPosition.set(position_);
}

void Player::tileChanged(const vector2dst &position_, const board::BoardTileData oldValue, const board::BoardTileData newValue)
{
    DisplayLog::info("Player (position ", position_, ") changed from ", oldValue, " to ", newValue);
    data.set(newValue);
}

} // namespace zoper
