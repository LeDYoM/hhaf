#include "boardgroup.hpp"
#include "token.hpp"
#include "tokenzones.hpp"
#include "player.hpp"

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene_nodes/include/tablenode.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/scene/include/scenemanager.hpp>

#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{
using namespace lib::scene;
using namespace lib::scene::nodes;

BoardGroup::BoardGroup(SceneNode *parent, str name, vector2dst size)
    : BaseClass{parent, std::move(name)}
{
    setTableSize(std::move(size));
}

BoardGroup::~BoardGroup() {}

void BoardGroup::onCreated()
{
    BaseClass::onCreated();

    Rectf32 textBox{scenePerspective()};
    position = textBox.leftTop();
    sceneNodeSize = textBox.size();

    const Rectf32 bBox(scenePerspective());

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
    using namespace lib::board;

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

Color BoardGroup::getBackgroundTileColor(const size_type level,
                                         vector2dst tilePosition, const bool isCenter) const
{
    if (level <= 25)
    {
        if (isCenter)
        {
            if (level < 9)
            {
                if (level % 2)
                {
                    return {10, 200, 50};
                }
                else if (!(level % 3))
                {
                    return {255, 70, 200};
                }
                else
                {
                    return {255, 100, 100};
                }
            }
            else
            {
                if (!(tilePosition.x % 2))
                {
                    return (level < 15) ? Color{128, 128, 128} : Color{255, 100, 100};
                }
                else
                {
                    return (level < 15) ? Color{225, 255, 255} : Color{100, 200, 200};
                }
            }
        }
        else
        {
            if (level < 2)
            {
                return colors::Black;
            }
            else if (level < 3)
            {
                return {255, 128, 0};
            }
            else if (level < 5)
            {
                return {100, 128, 255};
            }
            else if (level < 10)
            {
                if (level % 2)
                {
                    return (tilePosition.x % 2) ? Color{0, 255, 255} : Color{255, 100, 200};
                }
                else
                {
                    return (tilePosition.y % 2) ? Color{0, 255, 255} : Color{255, 100, 200};
                }
            }
            else if (level < 15)
            {
                if (level % 2)
                {
                    if (tilePosition.x % 2)
                    {
                        return (tilePosition.y % 2) ? colors::White : Color{100, 100, 100};
                    }
                    else
                    {
                        return (tilePosition.y % 2) ? Color{0, 128, 255} : Color{10, 250, 100};
                    }
                }
                else
                {
                    return (tilePosition.x % 2) ? ((tilePosition.y % 2) ? Color{25, 25, 25} : Color{10, 12, 250}) : ((tilePosition.y % 2) ? Color{250, 50, 10} : Color{10, 200, 10});
                }
            }
        }
    }
    return colors::Black;
}

vector2df BoardGroup::board2SceneFactor() const
{
    return sceneManager().viewRect().size() / p_boardModel->size();
}

vector2df BoardGroup::board2Scene(const lib::vector2dst &bPosition) const
{
    return board2SceneFactor() * bPosition;
}

vector2df BoardGroup::tileSize() const
{
    return board2Scene({1, 1});
}

} // namespace zoper
