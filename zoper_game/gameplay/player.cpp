#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"
#include "boardgroup.hpp"
#include <boardmanager/include/boardmanager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::render;
using namespace haf::time;
using namespace haf::anim;
using namespace fmath;

namespace zoper
{
void Player::onAttached()
{
    m_renderizable_scene_node = attachedNode()
                                    ->createSceneNode("renderizable_scene_node")
                                    ->component<Renderizable>();
    m_renderizable_scene_node->renderizableBuilder()
        .name("player_render_scene_node")
        .figType(FigType_t::PolygonSprite)
        .pointCount(3U)
        .create();
}

void Player::update()
{
    Base::update();

    if (player_board_position.readResetHasChanged())
    {
        DisplayLog::info("Player board position: ", boardPosition());
        attachedNode()->Position = board2Scene(boardPosition());
        DisplayLog::info("Player scene position: ", attachedNode()->Position());
    }

    if (currentDirection.readResetHasChanged())
    {
        auto const direction{currentDirection()};
        m_renderizable_scene_node->attachedNode()->Rotation = direction.angle();
    }
}

bool Player::canBeMovedTo(BoardPositionType const& dest_position) const
{
    return TokenZones::pointInCenter(dest_position);
}

void Player::tileMoved(BoardPositionType const& source)
{
    Base::tileMoved(source);
    DisplayLog::info("Player old board position: ", source);
    LogAsserter::log_assert(boardPosition() != source,
                            "Source and dest are the same!");
    DisplayLog::info("Player board position: ", boardPosition());
    attachedNode()->Position = board2Scene(boardPosition());
    DisplayLog::info("Player scene position: ", attachedNode()->Position());

    player_board_position = boardPosition();
    currentDirection      = fromPositions(source, boardPosition());
}

void Player::launchPlayerAnimation(vector2df const& toWhere)
{
    attachedNode()->component(animation_component_);

    auto property_animation_builder{
        animation_component_->make_property_animation_builder(
            &SceneNode::Position, attachedNode()->Position(), toWhere)};

    property_animation_builder
        .duration(TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep))
        .actionWhenFinished(
            [this, currentPosition = attachedNode()->Position()]() {
                launchAnimationBack(currentPosition);
            });
    animation_component_->addAnimation(htps::move(property_animation_builder));
}

void Player::launchAnimationBack(SceneCoordinates const& toWhere)
{
    DisplayLog::info("Creating animation for player to go back");
    currentDirection = currentDirection().negate();
    attachedNode()->component(animation_component_);

    auto property_animation_builder{
        animation_component_->make_property_animation_builder(
            &SceneNode::Position, attachedNode()->Position(), toWhere)};
    property_animation_builder.duration(TimePoint_as_miliseconds(
        gameplay::constants::MillisAnimationLaunchPlayerStep));
    animation_component_->addAnimation(htps::move(property_animation_builder));
}

void Player::tileAdded()
{
    DisplayLog::info("TokenPlayer appeared at ", boardPosition());
    m_renderizable_scene_node->first()->material().color = getColorForToken();

    // Set the position in the scene depending on the board position
    player_board_position = boardPosition();
}

void Player::setTokenColor(scene::Color const& token_color)
{
    m_renderizable_scene_node->first()->material().color = token_color;
}

void Player::tileChanged(BoardTileData const oldValue,
                         BoardTileData const newValue)
{
    Base::tileChanged(oldValue, newValue);
    DisplayLog::info("Player (position ", boardPosition(), ") changed from ",
                     oldValue, " to ", newValue);
}

}  // namespace zoper
