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
    animation_component_{getOrCreateComponent<anim::AnimationComponent>()}
{}

Token::~Token() = default;

void Token::onCreated()
{
    ++tile_counter_;
    m_renderizable = createSceneNode<RenderizableSceneNode>("renderizable");
    m_renderizable->renderizableBuilder()
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
    auto const endScale{Scale()};

    {
        auto property_animation_builder{
            animation_component_->make_property_animation_builder(
                &Transformation::Scale, {0.0F, 0.0F}, endScale)};
        property_animation_builder.duration(AppearTokenTime);
        animation_component_->addAnimation(
            htps::move(property_animation_builder));
    }
}

void Token::setTokenColor(scene::Color const& token_color)
{
    m_renderizable->node()->material().color = token_color;
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
        animation_component_->make_property_animation_builder(
            &Transformation::Position, Position(), destination)};
    property_animation_builder.duration(time::TimePoint_as_miliseconds(1000U));
    animation_component_->addAnimation(htps::move(property_animation_builder));
}
}  // namespace zoper
