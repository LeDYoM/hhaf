#include "token.hpp"

#include <lib/scene/ianimation.hpp>
#include <lib/include/liblog.hpp>

#include "gamescene.hpp"
#include "levelproperties.hpp"

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::board;

u32 Token::m_tileCounter{0};

Token::Token(SceneNode *const parent, str name) : GameBaseTile{parent, name + str::to_str(m_tileCounter) + str::to_str(m_tileCounter)}
{
    ++m_tileCounter;
    m_node = createRenderizable(
        "Node" + str::to_str(m_tileCounter), FigType_t::Shape, 30U);
    animation_component_ = addComponentOfType<scene::AnimationComponent>();
}

Token::~Token() = default;

void Token::configure(sptr<LevelProperties> level_properties,
                  board::BoardTileData board_tile_data,
                  const Rectf32 &box)
{
    data.set(board_tile_data);
    m_node->box = box;
    m_node->color = getColorForToken();
    level_properties_ = std::move(level_properties);
}

void Token::resetTileCounter()
{
    m_tileCounter = 0;
}

void Token::tileAdded(const vector2dst &position_)
{
    DisplayLog::info("Token ", name(), " appeared at ", position_);
    // Set the position in the scene depending on the board position
    //        setBoardPosition(position);
}

void Token::tileRemoved(const vector2dst &position_)
{
    DisplayLog::info("Deleting token ", name(), " from scene at position ", position_);
}

void Token::tileChanged(const vector2dst &position_, const board::BoardTileData oldValue, const board::BoardTileData newValue)
{
    DisplayLog::info("Token at position ", position_, " changed from ", oldValue, " to ", newValue);
    data.set(newValue);
}

void Token::tileMoved(const vector2dst & /*source*/, const vector2dst &dest)
{
    const auto time(TimePoint_as_miliseconds(
        level_properties_->millisBetweenTokens() / 2));

    const auto destination(ancestor<GameScene>()->board2Scene(dest));
    animation_component_->addPropertyAnimation(time, position, destination);
}
} // namespace zoper
