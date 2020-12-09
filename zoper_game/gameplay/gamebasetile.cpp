#include "gamebasetile.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"

#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace haf::board;
using namespace haf::scene;
using namespace mtps;

namespace zoper
{
GameBaseTile::GameBaseTile(mtps::rptr<SceneNode> const parent, str name) :
    ITile{}, SceneNode{parent, std::move(name)}
{}

GameBaseTile::~GameBaseTile() = default;

mtps::rptr<BoardGroup> GameBaseTile::getBoardGroup()
{
    return ancestor<BoardGroup>();
}

void GameBaseTile::tileAdded(const mtps::vector2dst& position)
{
    TileBase::tileAdded(position);
    is_in_center = TokenZones::pointInCenter(position);
}

void GameBaseTile::tileMoved(const mtps::vector2dst&  source,
                        const mtps::vector2dst&  dest)
{
    TileBase::tileMoved(source, dest);
    is_in_center = TokenZones::pointInCenter(dest);
}

void GameBaseTile::tileChanged(const mtps::vector2dst& /*position */,
                               const BoardTileData /* oldValue */,
                               const BoardTileData /* newValue */)
{
    if (node_)
    {
        node_->color = getColorForToken();
    }
}

Color GameBaseTile::getColorForToken() const
{
    switch (value())
    {
    case 0:
        return colors::Red;
        break;
    case 1:
        return colors::Green;
        break;
    case 2:
        return colors::Blue;
        break;
    case 3:
        return colors::Yellow;
        break;
    case 4:
        return colors::Magenta;
        break;
    default:
        haf::DisplayLog::error("Error value for token: ", value(),
                               " is not supported");
        return colors::White;
        break;
    }
}

sptr<BoardManager> GameBaseTile::getBoardManager()
{
    auto board_group{ancestor<BoardGroup>()};
    LogAsserter::log_assert(board_group != nullptr, "Invalid BoardModel found");

    return board_group != nullptr ? board_group->boardModel() : nullptr;
}

}  // namespace zoper