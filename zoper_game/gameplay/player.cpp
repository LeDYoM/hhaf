#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"
#include "boardgroup.hpp"
#include <boardmanager/include/boardmanager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::render;
using namespace haf::time;
using namespace haf::anim;

namespace zoper
{
Player::Player(rptr<SceneNode> parent, str name) :
    BaseClass{htps::move(parent), htps::move(name)},
    player_board_position{},
    currentDirection{Direction{Direction::DirectionData::Up}}
{
    m_renderizable_scene_node =
        createSceneNode<RenderizableSceneNode>("renderizable_scene_node");
    m_renderizable_scene_node->renderizableBuilder()
        .name("player_render_scene_node")
        .figType(FigType_t::PolygonSprite)
        .pointCount(3U)
        .create();
}

Player::~Player() = default;

void Player::update()
{
    BaseClass::update();

    if (player_board_position.readResetHasChanged())
    {
        logger::DisplayLog::info("Player board position: ", boardPosition());
        Position = board2Scene(boardPosition());
        logger::DisplayLog::info("Player scene position: ", Position());
    }

    if (currentDirection.readResetHasChanged())
    {
        auto const direction{currentDirection()};
        m_renderizable_scene_node->Rotation = direction.angle();
    }
}

bool Player::canBeMovedTo(BoardPositionType const& dest_position) const
{
    return TokenZones::pointInCenter(dest_position);
}

void Player::tileMoved(BoardPositionType const& source)
{
    BaseClass::tileMoved(source);
    logger::DisplayLog::info("Player old board position: ", source);
    LogAsserter::log_assert(boardPosition() != source,
                            "Source and dest are the same!");
    logger::DisplayLog::info("Player board position: ", boardPosition());
    Position = board2Scene(boardPosition());
    logger::DisplayLog::info("Player scene position: ", Position());

    player_board_position = boardPosition();
    currentDirection      = fromPositions(source, boardPosition());
}

void Player::launchPlayerAnimation(vector2df const& toWhere)
{
    getOrCreateComponent(animation_component_);

    auto property_animation_builder{
        animation_component_->make_property_animation_builder(
            &Player::Position, Player::Position(), toWhere)};
    property_animation_builder
        .duration(TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep))
        .actionWhenFinished([this, currentPosition = Position()]() {
            launchAnimationBack(currentPosition);
        });
    animation_component_->addAnimation(htps::move(property_animation_builder));
}

void Player::launchAnimationBack(SceneCoordinates const& toWhere)
{
    logger::DisplayLog::info("Creating animation for player to go back");
    currentDirection = currentDirection().negate();
    getOrCreateComponent(animation_component_);

    auto property_animation_builder{
        animation_component_->make_property_animation_builder(
            &Player::Position, Position(), toWhere)};
    property_animation_builder.duration(TimePoint_as_miliseconds(
        gameplay::constants::MillisAnimationLaunchPlayerStep));
    animation_component_->addAnimation(htps::move(property_animation_builder));
}

void Player::tileAdded()
{
    logger::DisplayLog::info("TokenPlayer appeared at ", boardPosition());
    m_renderizable_scene_node->node()->material().color = getColorForToken();

    // Set the position in the scene depending on the board position
    player_board_position = boardPosition();
}

void Player::setTokenColor(scene::Color const& token_color)
{
    m_renderizable_scene_node->node()->material().color = token_color;
}

void Player::tileChanged(BoardTileData const oldValue,
                         BoardTileData const newValue)
{
    BaseClass::tileChanged(oldValue, newValue);
    logger::DisplayLog::info("Player (position ", boardPosition(), ") changed from ",
                     oldValue, " to ", newValue);
}

}  // namespace zoper
