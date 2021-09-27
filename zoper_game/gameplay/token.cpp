#include "token.hpp"

#include <hlog/include/hlog.hpp>

#include "gamescene.hpp"
#include "levelproperties.hpp"
#include "tokenzones.hpp"

#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/component/component_container.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;
using namespace haf::board;

namespace zoper
{

u32 Token::tile_counter_{0};

Token::Token(SceneNode* const parent, str name) :
    GameBaseTile{
        parent, name + str::to_str(tile_counter_) + str::to_str(tile_counter_)},
    animation_component_{components().component<anim::AnimationComponent>()}
{
    ++tile_counter_;
    buildNode(renderizableBuilder()
                  .name("Node" + str::to_str(tile_counter_))
                  .figType(FigType_t::Shape)
                  .pointCount(30U));
}

Token::~Token() = default;

void Token::setBox(const Rectf32& box)
{
    node()->box = box;
}

bool Token::canBeMoved(BoardPosition_t const&) const
{
    return true;
    //    return !TokenZones::pointInCenter(dest_position);
}

void Token::resetTileCounter()
{
    tile_counter_ = 0U;
}

void Token::tileAdded(const BoardPosition_t& position_)
{
    BaseClass::tileAdded(position_);
    DisplayLog::info("Token ", name(), " appeared at ", position_);

    auto const AppearTokenTime = time::TimePoint_as_miliseconds(1000U);
    auto const nodeBox{node()->box().size() / 2.0F};

    reserveExtraTransformations(2U);
    auto const newTransformationPosition{addTransformation()};
    auto const newTransformationScale{addTransformation()};

    {
        auto property_animation_builder{
            animation_component_
                ->make_property_animation_builder<Scale, Transformation>(
                    &(getTransformation(newTransformationScale)))};
        property_animation_builder.startValue(Scale::Zeros)
            .endValue(Scale::Ones)
            .duration(AppearTokenTime);
        animation_component_->addAnimation(
            std::move(property_animation_builder));
    }

    {
        auto property_animation_builder{
            animation_component_
                ->make_property_animation_builder<Position, Transformation>(
                    &(getTransformation(newTransformationPosition)))};
        property_animation_builder.startValue(nodeBox)
            .endValue(Position::value_type{0.0F, 0.0F})
            .duration(AppearTokenTime);
        animation_component_->addAnimation(
            std::move(property_animation_builder));
    }
}

void Token::tileRemoved(const BoardPosition_t& position_)
{
    BaseClass::tileRemoved(position_);
    DisplayLog::info("Deleting token ", name(), " from scene at position ",
                     position_);
}

void Token::tileChanged(const BoardPosition_t& position_,
                        const BoardTileData oldValue,
                        const BoardTileData newValue)
{
    BaseClass::tileChanged(position_, oldValue, newValue);
    DisplayLog::info("Token at position ", position_, " changed from ",
                     oldValue, " to ", newValue);
}

void Token::tileMoved(const BoardPosition_t& source,
                      const BoardPosition_t& dest)
{
    BaseClass::tileMoved(source, dest);
    auto const destination{board2Scene(dest)};

    auto property_animation_builder{
        animation_component_
            ->make_property_animation_builder_from_attached<Position, Token>()};
    property_animation_builder.startValue(prop<Position>()())
        .endValue(destination)
        .duration(time::TimePoint_as_miliseconds(1000U));
    animation_component_->addAnimation(std::move(property_animation_builder));
}
}  // namespace zoper
