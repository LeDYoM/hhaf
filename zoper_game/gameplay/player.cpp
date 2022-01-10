#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"
#include "boardgroup.hpp"
#include <boardmanager/include/boardmanager.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/scene_nodes/renderizable_scene_node.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/component/component_container.hpp>

namespace zoper
{
using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;
using namespace haf::time;
using namespace haf::anim;

Player::Player(types::rptr<SceneNode> parent, types::str name) :
    BaseClass{std::move(parent), std::move(name)},
    boardPosition{},
    currentDirection{Direction{Direction::DirectionData::Up}}
{
    buildNode(renderizableBuilder()
                  .name("player_render_scene_node")
                  .figType(FigType_t::Shape)
                  .pointCount(3U)
                  .box(rectFromSize(board2Scene({1, 1}))));

    reserveExtraTransformations(4U);
    move_in_  = addTransformation();
    rotator_  = addTransformation();
    scalator_ = addTransformation();
    move_out_ = addTransformation();
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
        auto const direction{currentDirection()};
        auto const tile_center{board2SceneFactor() / 2.0F};

        getTransformation(move_in_).prop<Position>() = tile_center;

        getTransformation(rotator_).prop<Rotation>().set(direction.angle());

        getTransformation(scalator_).prop<Scale>().set(
            (direction.isVertical())
                ? vector2df{board2SceneFactor().y / board2SceneFactor().x,
                            board2SceneFactor().x / board2SceneFactor().y}
                : vector2df{1.0F, 1.0F});

        getTransformation(move_out_).prop<Position>() = -tile_center;
    }
}

bool Player::canBeMoved(BoardPositionType const& dest_position) const
{
    return TokenZones::pointInCenter(dest_position);
}

void Player::movePlayer(Direction const& direction)
{
    LogAsserter::log_assert(direction.isValid(),
                            "Invalid direction passed to move");
    currentDirection = direction;
    auto nPosition{currentDirection().applyToVector(boardPosition())};
    if (getBoardManager()->moveTile(boardPosition(), nPosition))
    {
        ++movements_;
    }
}

void Player::tileMoved(BoardPositionType const& source,
                       BoardPositionType const& dest)
{
    BaseClass::tileMoved(source, dest);
    DisplayLog::info("Player board position: ", dest);
    prop<Position>() = board2Scene(dest);
    DisplayLog::info("Player scene position: ", prop<Position>().get());

    boardPosition = dest;
}

void Player::launchPlayerAnimation(vector2df const& toWhere)
{
    component(animation_component_);

    auto property_animation_builder{
        animation_component_->make_property_animation_builder_from_attached<
            Position, Player>()};
    property_animation_builder.startValue(prop<Position>()())
        .endValue(toWhere)
        .duration(TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep))
        .actionWhenFinished([this, currentPosition = prop<Position>()()]() {
            launchAnimationBack(currentPosition);
        });
    animation_component_->addAnimation(std::move(property_animation_builder));
}

void Player::launchAnimationBack(SceneCoordinates const& toWhere)
{
    DisplayLog::info("Creating animation for player to go back");
    currentDirection = currentDirection().negate();
    component(animation_component_);

    auto property_animation_builder{
        animation_component_->make_property_animation_builder<Position, Player>(
            this)};
    property_animation_builder.startValueIsCurrent().endValue(toWhere).duration(
        TimePoint_as_miliseconds(
            gameplay::constants::MillisAnimationLaunchPlayerStep));
    animation_component_->addAnimation(std::move(property_animation_builder));
}

void Player::tileAdded(BoardPositionType const& position_)
{
    DisplayLog::info("TokenPlayer appeared at ", position_);
    node()->prop<render::ColorProperty>().set(getColorForToken());

    // Set the position in the scene depending on the board position
    boardPosition.set(position_);
}

void Player::tileChanged(BoardPositionType const& position_,
                         BoardTileData const oldValue,
                         BoardTileData const newValue)
{
    BaseClass::tileChanged(position_, oldValue, newValue);
    DisplayLog::info("Player (position ", position_, ") changed from ",
                     oldValue, " to ", newValue);
}

}  // namespace zoper
