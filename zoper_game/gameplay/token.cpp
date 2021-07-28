#include "token.hpp"

#include <hlog/include/hlog.hpp>

#include "gamescene.hpp"
#include "levelproperties.hpp"
#include "tokenzones.hpp"

#include <haf/include/render/renderizables.hpp>
#include <haf/include/render/renderizable_builder.hpp>
#include <haf/include/components/component_container.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::render;
using namespace haf::board;

namespace zoper
{

u32 Token::m_tileCounter{0};

Token::Token(SceneNode* const parent, str name) :
    GameBaseTile{parent,
                 name + str::to_str(m_tileCounter) + str::to_str(m_tileCounter)}
{
    ++m_tileCounter;
    buildNode(renderizableBuilder()
                  .name("Node" + str::to_str(m_tileCounter))
                  .figType(FigType_t::Shape)
                  .pointCount(30U));
    animation_component_ =
        components().addComponentOfType<scene::AnimationComponent>();
}

Token::~Token() = default;

void Token::setBox(const Rectf32& box)
{
    node()->box = box;
}

bool Token::canBeMoved(htps::vector2dst const&) const
{
    return true;
    //    return !TokenZones::pointInCenter(dest_position);
}

void Token::resetTileCounter()
{
    m_tileCounter = 0U;
}

void Token::tileAdded(const vector2dst& position_)
{
    BaseClass::tileAdded(position_);
    DisplayLog::info("Token ", name(), " appeared at ", position_);

    auto const AppearTokenTime = time::TimePoint_as_miliseconds(1000U);
    auto const nodeBox{node()->box().size() / 2.0F};

    auto newTransformationPosition = addTransformation();
    auto newTransformationScale    = addTransformation();

    animation_component_->addPropertyAnimation(
        AppearTokenTime,
        getTransformation(newTransformationScale).prop<Scale>(), Scale::Zeros,
        Scale::Ones);

    getTransformation(newTransformationPosition)
        .prop<Position>()
        .set(Position::value_type{nodeBox});
    animation_component_->addPropertyAnimation(
        AppearTokenTime,
        getTransformation(newTransformationPosition).prop<Position>(), nodeBox,
        Position::value_type{0.0F, 0.0F});
}

void Token::tileRemoved(const vector2dst& position_)
{
    BaseClass::tileRemoved(position_);
    DisplayLog::info("Deleting token ", name(), " from scene at position ",
                     position_);
}

void Token::tileChanged(const vector2dst& position_,
                        const BoardTileData oldValue,
                        const BoardTileData newValue)
{
    BaseClass::tileChanged(position_, oldValue, newValue);
    DisplayLog::info("Token at position ", position_, " changed from ",
                     oldValue, " to ", newValue);
}

void Token::tileMoved(const vector2dst& source, const vector2dst& dest)
{
    BaseClass::tileMoved(source, dest);

    auto const MoveTokenTime = time::TimePoint_as_miliseconds(1000U);

    const auto destination(board2Scene(dest));
    animation_component_->addPropertyAnimation(MoveTokenTime, prop<Position>(),
                                               prop<Position>()(), destination);
}
}  // namespace zoper
