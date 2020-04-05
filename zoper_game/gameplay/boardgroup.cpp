#include "boardgroup.hpp"
#include "token.hpp"
#include "tokenzones.hpp"
#include "player.hpp"

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene_nodes/include/tablenode.hpp>
#include <lib/scene_components/include/scenemetrics.hpp>
#include <lib/scene/include/renderizable.hpp>

#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/itile.hpp>

using namespace mtps;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{

BoardGroup::BoardGroup(SceneNode *parent, str name, vector2dst size)
    : BaseClass{parent, std::move(name)}
{
    setTableSize(std::move(size));
}

BoardGroup::~BoardGroup() {}

void BoardGroup::onCreated()
{
    BaseClass::onCreated();

    Rectf32 textBox{dataWrapper<SceneMetrics>()->currentView()};
    position = textBox.leftTop();
    sceneNodeSize = textBox.size();

    const Rectf32 bBox(textBox);

    Rectf32 tileBox({}, cellSize());
    for (size_type y{0U}; y < tableSize().y; ++y)
    {
        for (size_type x{0U}; x < tableSize().x; ++x)
        {
            static_cast<void>(createNodeAt({x, y}, make_str("BoardGroupTile_", x, y), tileBox));
        }
    }

    p_boardModel = addComponentOfType<board::BoardModelComponent>();
    p_boardModel->initialize(tableSize(), this);

    tokens_scene_node = createSceneNode("tokens_scene_node");
    addPlayer();
}

void BoardGroup::configure(sptr<LevelProperties> level_properties)
{
    level_properties_ = std::move(level_properties);
}

void BoardGroup::addPlayer()
{
    DisplayLog::info("Adding player tile at ", TokenZones::centerRect.leftTop());
    log_assert(player_ == nullptr, "Player already initialized");
    // Create the player instance
    player_ = tokens_scene_node->createSceneNode<Player>("playerNode");
    player_->configure(TokenZones::centerRect.leftTop(),
                       rectFromSize(tileSize()), board2SceneFactor());

    // Add it to the board and to the scene nodes
    p_boardModel->setTile(player_->boardPosition(), player_);
}

void BoardGroup::createNewToken(
    const board::BoardTileData data,
    const vector2dst &board_position,
    const vector2df &size)
{
    using namespace haf::board;

    DisplayLog::info("BoardGroup:: Adding new token at ", board_position,
                     " with value ", data);

    // Create a new Tile instance
    auto new_tile_token = tokens_scene_node->createSceneNode<Token>("tileNode");
    new_tile_token->configure(
        level_properties_,
        static_cast<BoardTileData>(data), rectFromSize(size),
        board2SceneFactor());

    // Set the position in the scene depending on the board position
    new_tile_token->position.set(board2Scene(board_position));

    // Add it to the board
    p_boardModel->setTile(board_position, std::move(new_tile_token));
}

void BoardGroup::tileRemoved(const vector2dst, board::SITilePointer &tile)
{
    log_assert(std::dynamic_pointer_cast<Token>(tile) != nullptr,
               "Trying to delete invalid type from board");
    tokens_scene_node->removeSceneNode(std::dynamic_pointer_cast<Token>(tile));
}

void BoardGroup::setLevel(const size_type level)
{
    // Update background tiles
    for_each_tableSceneNode([this, level](const auto position, auto node) {
        node->setTileColor(getBackgroundTileColor(level, position, TokenZones::pointInCenter(position)));
    });
}

Color BoardGroup::getBackgroundTileColor(
    const size_type level, vector2dst tilePosition, const bool isCenter) const
{
    if (level <= 25U)
    {
        if (isCenter)
        {
            if (level < 9U)
            {
                if (level % 2U)
                {
                    return {10U, 200U, 50U};
                }
                else if (!(level % 3U))
                {
                    return {255U, 70U, 200U};
                }
                else
                {
                    return {255U, 100U, 100U};
                }
            }
            else
            {
                if (!(tilePosition.x % 2U))
                {
                    return (level < 15U) ? Color{128U, 128U, 128U} : Color{255U, 100U, 100U};
                }
                else
                {
                    return (level < 15U) ? Color{225U, 255U, 255U} : Color{100U, 200U, 200U};
                }
            }
        }
        else
        {
            if (level < 2U)
            {
                return colors::Black;
            }
            else if (level < 3U)
            {
                return {255U, 128U, 0U};
            }
            else if (level < 5U)
            {
                return {100U, 128U, 255U};
            }
            else if (level < 10U)
            {
                if (level % 2U)
                {
                    return (tilePosition.x % 2U) ? Color{0U, 255U, 255U} : Color{255U, 100U, 200U};
                }
                else
                {
                    return (tilePosition.y % 2U) ? Color{0U, 255U, 255U} : Color{255U, 100U, 200U};
                }
            }
            else if (level < 15U)
            {
                if (level % 2U)
                {
                    if (tilePosition.x % 2U)
                    {
                        return (tilePosition.y % 2U) ? colors::White : Color{100U, 100U, 100U};
                    }
                    else
                    {
                        return (tilePosition.y % 2U) ? Color{0U, 128U, 255U} : Color{10U, 250U, 100U};
                    }
                }
                else
                {
                    return (tilePosition.x % 2U) ? ((tilePosition.y % 2U) ? Color{25U, 25U, 25U} : Color{10U, 12U, 250U}) : ((tilePosition.y % 2U) ? Color{250U, 50U, 10U} : Color{10U, 200U, 10U});
                }
            }
        }
    }
    return colors::Black;
}

vector2df BoardGroup::board2SceneFactor() const
{
    return dataWrapper<SceneMetrics>()->currentView().size() / p_boardModel->size();
}

vector2df BoardGroup::board2Scene(const vector2dst &bPosition) const
{
    return board2SceneFactor() * bPosition;
}

vector2df BoardGroup::tileSize() const
{
    return board2Scene({1, 1});
}

} // namespace zoper