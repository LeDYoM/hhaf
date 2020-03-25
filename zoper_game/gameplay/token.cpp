#include "token.hpp"

#include <lib/include/liblog.hpp>

#include "gamescene.hpp"
#include "levelproperties.hpp"

using namespace mtps;
using namespace lib;
using namespace lib::scene;
using namespace lib::board;

namespace zoper
{

u32 Token::m_tileCounter{0};

Token::Token(SceneNode *const parent, str name)
    : GameBaseTile{parent, name + str::to_str(m_tileCounter) + str::to_str(m_tileCounter)}
{
    ++m_tileCounter;
    m_node = createRenderizable(
        "Node" + mtps::str::to_str(m_tileCounter), FigType_t::Shape, 30U);
    animation_component_ = addComponentOfType<scene::AnimationComponent>();
}

Token::~Token() = default;

void Token::configure(sptr<LevelProperties> level_properties,
                      board::BoardTileData board_tile_data,
                      const Rectf32 &box,
                      const vector2df &board2SceneFactor)
{
    data.set(board_tile_data);
    m_node->box = box;
    m_node->color = getColorForToken();
    level_properties_ = std::move(level_properties);
    board2SceneFactor_ = board2SceneFactor;
}

void Token::resetTileCounter()
{
    m_tileCounter = 0U;
}

void Token::tileAdded(const vector2dst &position_)
{
    DisplayLog::info("Token ", name(), " appeared at ", position_);
}

void Token::tileRemoved(const vector2dst &position_)
{
    DisplayLog::info("Deleting token ", name(),
                     " from scene at position ", position_);
}

void Token::tileChanged(const vector2dst &position_,
                        const board::BoardTileData oldValue,
                        const board::BoardTileData newValue)
{
    DisplayLog::info("Token at position ", position_,
                     " changed from ", oldValue, " to ", newValue);
    data.set(newValue);
}

void Token::tileMoved(const vector2dst & /*source*/, const vector2dst &dest)
{
    const auto time(time::TimePoint_as_miliseconds(
        level_properties_->millisBetweenTokens() / 2));

    const auto destination(board2SceneFactor_ * dest);
    animation_component_->addPropertyAnimation(
        time, position, position(), destination);
}
} // namespace zoper
