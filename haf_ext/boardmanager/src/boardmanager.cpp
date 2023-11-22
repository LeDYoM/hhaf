#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/iboardmanageractuator.hpp>

#include <hlog/include/hlog.hpp>

#include <utility>

using namespace htps;

namespace haf::board
{
void BoardManager::initialize(
    vector2dst const& size,
    rptr<IBoardManagerActuator> board_manager_actuator)
{
    logger::DisplayLog::info("BoardManager initialize with size: ", size);
    logger::DisplayLog::info("IBoardManagerActuator received: ",
                     (board_manager_actuator != nullptr));

    LogAsserter::log_assert(actuator_ == nullptr,
                            "m_actuator already contains a value");
    std::swap(actuator_, board_manager_actuator);
    initializeTileMatrix(size);
}

void BoardManager::initializeTileMatrix(fmath::vector2dst const& size)
{
    // Create the tiles.
    tiles_.reserve(size.x);
    for (decltype(size.x) x{0U}; x < size.x; ++x)
    {
        tiles_.emplace_back(size.y);
        for (decltype(size.y) y{0U}; y < size.y; ++y)
        {
            tiles_[x].emplace_back();
        }
    }
    tiles_.shrink_to_fit();
}

BoardManager::BackgroundFunction BoardManager::setBackgroundFunction(
    BoardManager::BackgroundFunction background_function)
{
    return std::exchange(background_function_, htps::move(background_function));
}

BoardManager::BackgroundData BoardManager::backgroundData(
    fmath::vector2dst const& tPosition) const
{
    if (background_function_ && validCoords(tPosition))
    {
        return background_function_(tPosition);
    }
    return BackgroundData{};
}

SITilePointer BoardManager::getTile(
    BoardPositionType const& position) const noexcept
{
    if (validCoords(position))
    {
        return tiles_[position.x][position.y];
    }

    logger::DisplayLog::error("Error getting tile in coordinates: ", position);
    return SITilePointer();
}

bool BoardManager::setTile(BoardPositionType const& tPosition,
                           SITilePointer newTile)
{
    LogAsserter::log_assert(tileEmpty(tPosition),
                            "You can only set data in empty tiles");

    if (tileEmpty(tPosition))
    {
        _setTile(tPosition, newTile);
        newTile->board_position = tPosition;
        newTile->tileAdded();

        if (actuator_)
        {
            actuator_->tileAdded(tPosition, newTile);
        }
        return true;
    }
    return false;
}

bool BoardManager::tileEmpty(BoardPositionType const& position) const noexcept
{
    return getTile(position) == nullptr;
}

bool BoardManager::deleteTile(BoardPositionType const& position)
{
    LogAsserter::log_assert(!tileEmpty(position),
                            "You can only delete not empty tiles");

    if (!tileEmpty(position))
    {
        SITilePointer current{getTile(position)};
        current->board_position = position;
        current->tileRemoved();

        if (actuator_)
        {
            actuator_->tileRemoved(position, current);
        }
        tiles_[position.x][position.y].reset();
        return true;
    }
    return false;
}

bool BoardManager::changeTileData(BoardPositionType const& source,
                                  BoardTileData const& new_value)
{
    LogAsserter::log_assert(!tileEmpty(source),
                            "You can only change data in not empty tiles");

    if (!tileEmpty(source))
    {
        auto tile{getTile(source)};
        BoardTileData old_value{tile->value()};

        if (actuator_)
        {
            actuator_->tileChanged(source, tile, old_value, new_value);
        }
        tile->data_ = new_value;
        tile->tileChanged(old_value, new_value);
        return true;
    }
    return false;
}

bool BoardManager::swapTileData(BoardPositionType const& lhs,
                                BoardPositionType const& rhs)
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

bool BoardManager::moveTile(BoardPositionType const source,
                            BoardPositionType const dest)
{
    if (!tileEmpty(source))
    {
        logger::DisplayLog::info("Moving tile from ", source, " to ", dest);

        SITilePointer sourceTile{getTile(source)};

        if (sourceTile)
        {
            // Check if we can move the tile sourceTile to its destination
            if (!sourceTile->canBeMovedTo(dest))
            {
                return false;
            }

            SITilePointer destTile{getTile(dest)};
            logger::DisplayLog::info("Source Value: ", sourceTile->value());
            LogAsserter::log_assert(
                destTile == nullptr,
                "Trying to move to a not empty tile: ", dest);

            if (destTile == nullptr)
            {
                _setTile(dest, sourceTile);
                _setTile(source, SITilePointer());
                sourceTile->board_position = dest;
                if (actuator_)
                {
                    actuator_->tileMoved(source, dest, sourceTile);
                }
                sourceTile->tileMoved(source);
                return true;
            }
            else
            {
                logger::DisplayLog::error("Trying to move to non empty tile");
                return false;
            }
        }
    }
    else
    {
        logger::DisplayLog::info("Trying to move empty tile: ", source.x, ",", source.y,
                         " ignoring it");
    }
    return false;
}

bool BoardManager::validCoords(
    BoardPositionType const& tPosition) const noexcept
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
    auto const _size{size()};
    str temp {_size.x * _size.y};

    for (u32 y{0}; y < _size.y; ++y)
    {
        for (u32 x{0}; x < _size.x; ++x)
        {
            str chTemp;
            SITilePointer lp_tile{getTile({x, y})};
            if (lp_tile)
            {
                chTemp = str::to_str(lp_tile->value());
            }
            else
            {
                auto const background_data{backgroundData({x, y})};
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

void BoardManager::_setTile(BoardPositionType const& position,
                            SITilePointer newTile)
{
    tiles_[position.x][position.y] = htps::move(newTile);
}
}  // namespace haf::board
