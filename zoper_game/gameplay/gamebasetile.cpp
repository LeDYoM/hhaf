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
    TileBase{}, BaseClass{parent, std::move(name)}
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

vector2df GameBaseTile::board2Scene(vector2dst const& bPosition) const
{
    return getBoardGroup()->board2Scene(bPosition);
}

void GameBaseTile::tileAdded()
{
    TileBase::tileAdded();
    is_in_center = TokenZones::pointInCenter(boardPosition());
}

void GameBaseTile::tileMoved(BoardPositionType const& source)
{
    TileBase::tileMoved(source);
    is_in_center = TokenZones::pointInCenter(boardPosition());
}

void GameBaseTile::tileChanged(BoardTileData const /* oldValue */,
                               BoardTileData const /* newValue */)
{
    if (node())
    {
        node()->prop<render::ColorProperty>() = getColorForToken();
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

bool GameBaseTile::isInCenter() const noexcept
{
    return is_in_center;
}

}  // namespace zoper
