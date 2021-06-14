#include "gamebasetile.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"

#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace haf::board;
using namespace haf::scene;
using namespace htps;

namespace zoper
{
GameBaseTile::GameBaseTile(rptr<SceneNode> const parent, str name) :
    ITile{}, BaseClass{parent, std::move(name)}
{}

GameBaseTile::~GameBaseTile() = default;

rptr<BoardGroup> GameBaseTile::getBoardGroup()
{
    return ancestor<BoardGroup>();
}

rptr<BoardGroup const> GameBaseTile::getBoardGroup() const
{
    return ancestor<BoardGroup>();
}

vector2df GameBaseTile::board2SceneFactor() const
{
    return getBoardGroup()->board2SceneFactor();
}

vector2df GameBaseTile::board2Scene(const vector2dst& bPosition) const
{
    return getBoardGroup()->board2Scene(bPosition);
}

void GameBaseTile::tileAdded(const vector2dst& position)
{
    TileBase::tileAdded(position);
    is_in_center = TokenZones::pointInCenter(position);
}

void GameBaseTile::tileMoved(const vector2dst&  source,
                        const vector2dst&  dest)
{
    TileBase::tileMoved(source, dest);
    is_in_center = TokenZones::pointInCenter(dest);
}

void GameBaseTile::tileChanged(const vector2dst& /*position */,
                               const BoardTileData /* oldValue */,
                               const BoardTileData /* newValue */)
{
    if (node())
    {
        node()->color = getColorForToken();
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
    auto board_group{getBoardGroup()};
    LogAsserter::log_assert(board_group != nullptr, "Invalid BoardModel found");

    return board_group != nullptr ? board_group->boardManager() : nullptr;
}

sptr<BoardManager const> const GameBaseTile::getBoardManager() const
{
    auto const board_group{getBoardGroup()};
    LogAsserter::log_assert(board_group != nullptr, "Invalid BoardModel found");

    return board_group != nullptr ? board_group->boardManager() : nullptr;
}

}  // namespace zoper