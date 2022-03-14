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
    animation_component_{component<anim::AnimationComponent>()}
{
}

Token::~Token() = default;

void Token::onCreated()
{
    ++tile_counter_;
    renderizableBuilder()
        .name("Node" + str::to_str(tile_counter_))
        .figType(FigType_t::PolygonSprite)
        .pointCount(30U)
        .create();
}

bool Token::canBeMovedTo(BoardPositionType const&) const
{
    return true;
}

void Token::resetTileCounter()
{
    tile_counter_ = 0U;
}

void Token::tileAdded()
{
    BaseClass::tileAdded();
    DisplayLog::info("Token ", name(), " appeared at ", boardPosition());

        auto const AppearTokenTime = time::TimePoint_as_miliseconds(1000U);
        auto const endScale{prop<Scale>()()};

        {
            auto property_animation_builder{
                animation_component_
                    ->make_property_animation_builder<Scale, Transformation>(
                        this)};
            property_animation_builder.startValue(Scale::Zeros)
                .endValue(endScale)
                .duration(AppearTokenTime);
            animation_component_->addAnimation(
                std::move(property_animation_builder));
        }

    /*
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
    */
}

void Token::tileRemoved()
{
    BaseClass::tileRemoved();
    DisplayLog::info("Deleting token ", name(), " from scene at position ",
                     boardPosition());
}

void Token::tileChanged(const BoardTileData oldValue,
                        const BoardTileData newValue)
{
    BaseClass::tileChanged(oldValue, newValue);
    DisplayLog::info("Token at position ", boardPosition(), " changed from ",
                     oldValue, " to ", newValue);
}

void Token::tileMoved(const BoardPositionType& source)
{
    BaseClass::tileMoved(source);
    auto const destination{board2Scene(boardPosition())};

    auto property_animation_builder{
        animation_component_
            ->make_property_animation_builder_from_attached<Position, Token>()};
    property_animation_builder.startValueIsCurrent()
        .endValue(destination)
        .duration(time::TimePoint_as_miliseconds(1000U));
    animation_component_->addAnimation(std::move(property_animation_builder));
}
}  // namespace zoper
