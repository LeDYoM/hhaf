#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/iboardmanageractuator.hpp>

#include <hlog/include/hlog.hpp>

#include <utility>

using namespace htps;

namespace haf::board
{

void BoardManager::initialize(
    const vector2dst& size,
    rptr<IBoardManagerActuator> board_manager_actuator)
{
    DisplayLog::info("BoardManager initialize with size: ", size);
    DisplayLog::info("IBoardManagerActuator received: ",
                     (board_manager_actuator != nullptr));

    LogAsserter::log_assert(actuator_ == nullptr,
                            "m_actuator already contains a value");
    std::swap(actuator_, board_manager_actuator);

    // Create the tiles.
    tiles_.reserve(size.x);
    for (auto x = 0U; x < size.x; ++x)
    {
        tiles_.emplace_back(size.y);
        for (auto y = 0U; y < size.y; ++y)
        {
            tiles_[x].emplace_back();
        }
    }
    tiles_.shrink_to_fit();
}

BackgroundFunction BoardManager::setBackgroundFunction(
    BackgroundFunction background_function)
{
    return std::exchange(background_function_, std::move(background_function));
}

BackgroundData BoardManager::backgroundType(
    const htps::vector2dst& tPosition) const
{
    if (background_function_ && validCoords(tPosition))
    {
        return background_function_(tPosition);
    }
    return BackgroundData{};
}

SITilePointer BoardManager::getTile(
    const vector2dst& position) const noexcept
{
    if (validCoords(position))
    {
        return tiles_[position.x][position.y];
    }

    DisplayLog::error("Error getting tile in coordinates: ", position);
    return SITilePointer();
}

bool BoardManager::setTile(const vector2dst& tPosition,
                                  SITilePointer newTile)
{
    LogAsserter::log_assert(tileEmpty(tPosition),
                            "You can only set data in empty tiles");

    if (tileEmpty(tPosition))
    {
        _setTile(tPosition, newTile);
        newTile->tileAdded(tPosition);

        if (actuator_)
        {
            actuator_->tileAdded(tPosition, newTile);
        }
        return true;
    }
    return false;
}

bool BoardManager::tileEmpty(const vector2dst& position) const noexcept
{
    return getTile(position) == nullptr;
}

bool BoardManager::deleteTile(const vector2dst& position)
{
    LogAsserter::log_assert(!tileEmpty(position),
                            "You can only delete not empty tiles");

    if (!tileEmpty(position))
    {
        SITilePointer current(getTile(position));
        current->tileRemoved(position);

        if (actuator_)
        {
            actuator_->tileRemoved(position, current);
        }
        tiles_[position.x][position.y].reset();
        return true;
    }
    return false;
}

bool BoardManager::changeTileData(const vector2dst& source,
                                         const BoardTileData& nv)
{
    LogAsserter::log_assert(!tileEmpty(source),
                            "You can only change data in not empty tiles");

    if (!tileEmpty(source))
    {
        auto tile{getTile(source)};
        BoardTileData ov{tile->value()};

        if (actuator_)
        {
            actuator_->tileChanged(source, tile, ov, nv);
        }
        tile->data_ = nv;
        tile->tileChanged(source, ov, nv);
        return true;
    }
    return false;
}

bool BoardManager::swapTileData(const vector2dst& lhs,
                                       const vector2dst& rhs)
{
    LogAsserter::log_assert(!tileEmpty(lhs),
                            "You can only change data in not empty tiles");
    LogAsserter::log_assert(!tileEmpty(rhs),
                            "You can only change data in not empty tiles");

    if (!tileEmpty(lhs) && !tileEmpty(rhs))
    {
        const BoardTileData temp{getTile(lhs)->value()};
        changeTileData(lhs, getTile(rhs)->value());
        changeTileData(rhs, temp);
        return true;
    }
    return false;
}

bool BoardManager::moveTile(const vector2dst& source,
                                   const vector2dst& dest)
{
    if (!tileEmpty(source))
    {
        DisplayLog::info("Moving tile from ", source, " to ", dest);

        SITilePointer sourceTile{getTile(source)};

        if (sourceTile)
        {
            // Check if we can move the tile sourceTile to its destination
            if (!sourceTile->canBeMoved(dest))
            {
                return false;
            }

            SITilePointer destTile{getTile(dest)};
            DisplayLog::info("Source Value: ", sourceTile->value());
            LogAsserter::log_assert(
                !destTile, "Trying to move to a not empty tile: ", dest);

            if (!destTile)
            {
                _setTile(dest, sourceTile);
                _setTile(source, SITilePointer());

                if (actuator_)
                {
                    actuator_->tileMoved(source, dest, sourceTile);
                }
                sourceTile->tileMoved(source, dest);
                return true;
            }
            else
            {
                DisplayLog::error("Trying to move to non empty tile");
                return false;
            }
            
        }
    }
    else
    {
        DisplayLog::info("Trying to move empty tile: ", source.x, ",", source.y,
                         " ignoring it");
    }
    return false;
}

bool BoardManager::validCoords(
    const vector2dst& tPosition) const noexcept
{
    return tiles_.size() > tPosition.x && tiles_[0U].size() > tPosition.y;
}

vector2dst BoardManager::size() const noexcept
{
    return !tiles_.empty() ? vector2dst{tiles_.size(), tiles_[0U].size()}
                           : vector2dst{0U, 0U};
}

str BoardManager::toStr()
{
    const auto _size{size()};
    str temp;

    for (u32 y{0}; y < _size.y; ++y)
    {
        for (u32 x{0}; x < _size.x; ++x)
        {
            str chTemp;
            SITilePointer lp_tile(getTile({x, y}));
            if (lp_tile)
            {
                chTemp = str::to_str(lp_tile->value());
            }
            else
            {
                BackgroundData background_data{backgroundType({x, y})};
                if (background_data == BackgroundData{})
                {
                    chTemp = "*";
                }
                else
                {
                    chTemp = "C";
                }
            }

            temp += chTemp;
        }
        temp += str("\n");
    }
    return temp;
}

void BoardManager::_setTile(const vector2dst& position,
                                   SITilePointer newTile)
{
    tiles_[position.x][position.y] = newTile;
}
}  // namespace haf::board
