#include "boardgroup.hpp"
#include "token.hpp"
#include "tokenzones.hpp"
#include "player.hpp"
#include "levelproperties.hpp"
#include "scoreutils.hpp"
#include "boardutils.hpp"

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_nodes/table_node.hpp>
#include <haf/include/scene_nodes/scene_node_size.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/scenenode_cast.hpp>
#include <haf/include/component/component_container.hpp>

#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/itile.hpp>

using namespace htps;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{

BoardGroup::~BoardGroup() = default;

void BoardGroup::configure(vector2dst size,
                           sptr<LevelProperties> level_properties)
{
    level_properties_ = std::move(level_properties);
    prop<TableSize>().set(size);
    auto const tableSize{prop<TableSize>().get()};

    Rectf32 textBox{subSystem<ISceneMetricsView>()->currentView()};
    prop<Position>() = textBox.leftTop();
    prop<SceneNodeSize>().set(textBox.size());

    Rectf32 const bBox{textBox};
    Rectf32 tileBox({}, cellSize());

    // Create the nodes to render the tiles
    for (size_type y{0U}; y < tableSize.y; ++y)
    {
        for (size_type x{0U}; x < tableSize.x; ++x)
        {
            auto node = createNodeAt({x, y}, make_str("BoardGroupTile_", x, y));
            node->prop<NodeSize>().set(tileBox);
        }
    }

    // Create and initialize the BoardManager
    auto board_model{component<board::BoardManager>()};
    board_model->initialize(tableSize, this);

    board_model->setBackgroundFunction(
        [](const vector2dst& position) -> board::BoardManager::BackgroundData {
            return ((TokenZones::pointInCenter(position)) ? (1) : (0));
        });

    tokens_scene_node = createSceneNode("tokens_scene_node");
    setLevel(level_properties_->currentLevel());
    addPlayer();

    level_properties_->levelChanged.connect(
        make_function(this, &BoardGroup::setLevel));
}

void BoardGroup::addPlayer()
{
    DisplayLog::info("Adding player tile at ",
                     TokenZones::centerRect.leftTop());
    LogAsserter::log_assert(player_ == nullptr, "Player already initialized");

    // Create the player instance
    player_ = tokens_scene_node->createSceneNode<Player>("playerNode");

    // Add it to the board and to the scene nodes
    componentOfType<board::BoardManager>()->setTile(
        TokenZones::centerRect.leftTop(), player_);
}

void BoardGroup::createNewToken(const BoardTileData data,
                                const vector2dst& board_position,
                                const vector2df& size)
{
    using namespace haf::board;

    DisplayLog::info("BoardGroup:: Adding new token at ", board_position,
                     " with value ", data);

    // Create a new Tile instance
    auto new_tile_token = tokens_scene_node->createSceneNode<Token>("tileNode");

    // Set the position in the scene depending on the board position
    new_tile_token->prop<Position>().set(board2Scene(board_position));
    new_tile_token->setBox(rectFromSize(size));

    // Add it to the board
    auto board_model{componentOfType<board::BoardManager>()};
    board_model->setTile(board_position, new_tile_token);
    board_model->changeTileData(board_position, data);
}

void BoardGroup::tileRemoved(const vector2dst, board::SITilePointer& tile)
{
    LogAsserter::log_assert(std::dynamic_pointer_cast<Token>(tile) != nullptr,
                            "Trying to delete invalid type from board");
    tokens_scene_node->removeSceneNode(std::dynamic_pointer_cast<Token>(tile));
}

void BoardGroup::setLevel(const size_type level)
{
    // Update background tiles
    for_each_tableSceneNode(
        [this, level](const auto position, sptr<BoardTileSceneNode> node) {
            node->prop<BoardTileSceneNodeProperties>().set<BackgroundColor>(
                getBackgroundTileColor(level, position,
                                       TokenZones::pointInCenter(position)));
        });
}

Color BoardGroup::getBackgroundTileColor(const size_type level,
                                         vector2dst tilePosition,
                                         const bool isCenter) const
{
    if (level <= 25U)
    {
        if (isCenter)
        {
            if (level < 9U)
            {
                if (level % 2U)
                {
                    return Color{10U, 200U, 50U};
                }
                else if (!(level % 3U))
                {
                    return Color{255U, 70U, 200U};
                }
                else
                {
                    return Color{255U, 100U, 100U};
                }
            }
            else
            {
                if (!(tilePosition.x % 2U))
                {
                    return (level < 15U) ? Color{128U, 128U, 128U}
                                         : Color{255U, 100U, 100U};
                }
                else
                {
                    return (level < 15U) ? Color{225U, 255U, 255U}
                                         : Color{100U, 200U, 200U};
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
                return Color{255U, 128U, 0U};
            }
            else if (level < 5U)
            {
                return Color{100U, 128U, 255U};
            }
            else if (level < 10U)
            {
                if (level % 2U)
                {
                    return (tilePosition.x % 2U) ? Color{0U, 255U, 255U}
                                                 : Color{255U, 100U, 200U};
                }
                else
                {
                    return (tilePosition.y % 2U) ? Color{0U, 255U, 255U}
                                                 : Color{255U, 100U, 200U};
                }
            }
            else if (level < 15U)
            {
                if (level % 2U)
                {
                    if (tilePosition.x % 2U)
                    {
                        return (tilePosition.y % 2U) ? colors::White
                                                     : Color{100U, 100U, 100U};
                    }
                    else
                    {
                        return (tilePosition.y % 2U) ? Color{0U, 128U, 255U}
                                                     : Color{10U, 250U, 100U};
                    }
                }
                else
                {
                    return (tilePosition.x % 2U)
                        ? ((tilePosition.y % 2U) ? Color{25U, 25U, 25U}
                                                 : Color{10U, 12U, 250U})
                        : ((tilePosition.y % 2U) ? Color{250U, 50U, 10U}
                                                 : Color{10U, 200U, 10U});
                }
            }
        }
    }
    return colors::Black;
}

bool BoardGroup::moveTileInDirection(Direction const direction,
                                     vector2dst const position)
{
    auto board_model{componentOfType<board::BoardManager>()};

    // Is the current tile position empty?
    if (!board_model->tileEmpty(position))
    {
        // If not, what about the next position to check, is empty?
        const auto next = direction.applyToVector(position);

        LogAsserter::log_assert(board_model->tileEmpty(next),
                                "Trying to move a token to a non empty tile");
        board_model->moveTile(position, next);
        return (TokenZones::toBoardBackgroundType(board_model->backgroundData(
                    next)) == TokenZones::BoardBackgroundType::Center);
    }
    return false;
}

bool BoardGroup::moveTowardsCenter(Direction const direction,
                                   vector2dst const& position)
{
    bool moved_to_center{false};
    auto board_model{componentOfType<board::BoardManager>()};

    // Is the current tile position empty?
    if (!board_model->tileEmpty(position))
    {
        // If not, what about the next position to check, is empty?
        const auto next = direction.applyToVector(position);

        if (!board_model->tileEmpty(next))
        {
            // If the target position where to move the
            // token is occupied, move the this target first.
            moved_to_center = moveTowardsCenter(direction, next);
        }
        board_model->moveTile(position, next);
        auto dest_tile{
            std::dynamic_pointer_cast<Token>(board_model->getTile(next))};

        LogAsserter::log_assert(dest_tile != nullptr, "Error moving the tile!");

        if (dest_tile->isInCenter())
        {
            LogAsserter::log_assert(!moved_to_center, "Double game over!");
            moved_to_center = true;
        }
    }
    return moved_to_center;
}

vector2df BoardGroup::board2SceneFactor() const
{
    return subSystem<ISceneMetricsView>()->currentView().size() /
        componentOfType<board::BoardManager>()->size();
}

vector2df BoardGroup::board2Scene(const vector2dst& bPosition) const
{
    return board2SceneFactor() * bPosition;
}

vector2df BoardGroup::tileSize() const
{
    return board2Scene({1, 1});
}

htps::sptr<board::BoardManager> BoardGroup::boardManager() noexcept
{
    return componentOfType<board::BoardManager>();
}

const htps::sptr<const board::BoardManager> BoardGroup::boardManager()
    const noexcept
{
    return componentOfType<board::BoardManager>();
}

htps::sptr<scene::SceneNode> BoardGroup::tokensSceneNode() noexcept
{
    return tokens_scene_node;
}

const htps::sptr<scene::SceneNode> BoardGroup::tokensSceneNode() const noexcept
{
    return tokens_scene_node;
}

htps::sptr<Player> BoardGroup::player() noexcept
{
    return player_;
}

const htps::sptr<Player> BoardGroup::player() const noexcept
{
    return player_;
}

}  // namespace zoper
