#include "token.hpp"

#include <hlog/include/hlog.hpp>

#include "gamescene.hpp"
#include "levelproperties.hpp"
#include "tokenzones.hpp"

using namespace mtps;
using namespace haf;
using namespace haf::scene;
using namespace haf::board;

namespace zoper
{

u32 Token::m_tileCounter{0};

Token::Token(SceneNode* const parent, str name) :
    GameBaseTile{parent,
                 name + str::to_str(m_tileCounter) + str::to_str(m_tileCounter)}
{
    ++m_tileCounter;
    node_ = renderizableBuilder()
                .name("Node" + str::to_str(m_tileCounter))
                .figType(FigType_t::Shape)
                .pointCount(30U)
                .create();
    animation_component_ = addComponentOfType<scene::AnimationComponent>();
}

Token::~Token() = default;

void Token::setBoxBoundaries(const Rectf32& box)
{
    node_->box = box;
}

bool Token::canBeMoved(mtps::vector2dst const&) const
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

    auto newTransformation = addTransformation();
    animation_component_->addPropertyAnimation(AppearTokenTime, prop<Scale>(),
                                               Scale::value_type{0.0F, 0.0F},
                                               Scale::value_type{1.0F, 1.0F});

    auto const nodeBox = node_->box().size() / 2.0F;

    animation_component_->addPropertyAnimation(
        AppearTokenTime, getTransformation(newTransformation).prop<Position>(),
        nodeBox, Position::value_type{0.0F, 0.0F});
}

void Token::tileRemoved(const vector2dst& position_)
{
    BaseClass::tileRemoved(position_);
    DisplayLog::info("Deleting token ", name(), " from scene at position ",
                     position_);
}

void Token::tileChanged(const vector2dst& position_,
                        const board::BoardTileData oldValue,
                        const board::BoardTileData newValue)
{
    BaseClass::tileChanged(position_, oldValue, newValue);
    DisplayLog::info("Token at position ", position_, " changed from ",
                     oldValue, " to ", newValue);
}

void Token::tileMoved(const vector2dst& source, const vector2dst& dest)
{
    BaseClass::tileMoved(source, dest);

    auto const MoveTokenTime = time::TimePoint_as_miliseconds(1000U);

    const auto destination(getBoardGroup()->board2Scene(dest));
    animation_component_->addPropertyAnimation(MoveTokenTime, prop<Position>(),
                                               prop<Position>()(), destination);
}
}  // namespace zoper
