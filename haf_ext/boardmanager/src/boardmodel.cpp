#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::board
{

void BoardModelComponent::initialize(
    const vector2dst& size,
    rptr<IBoardModelActuator> board_model_actuator)
{
    DisplayLog::info("BoardModelComponent initialize with size: ", size);
    DisplayLog::info("IBoardModelActuator received: ",
                     (board_model_actuator != nullptr));

    log_assert(actuator_ == nullptr, "m_actuator already contains a value");
    std::swap(actuator_, board_model_actuator);

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

SITilePointer BoardModelComponent::getTile(
    const vector2dst& position) const noexcept
{
    if (validCoords(position))
    {
        return tiles_[position.x][position.y];
    }

    DisplayLog::error("Error getting tile in coordinates: ", position);
    return SITilePointer();
}

bool BoardModelComponent::setTile(const vector2dst& tPosition,
                                  SITilePointer newTile)
{
    log_assert(tileEmpty(tPosition), "You can only set data in empty tiles");

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

bool BoardModelComponent::tileEmpty(const vector2dst& position) const noexcept
{
    return getTile(position) == nullptr;
}

bool BoardModelComponent::deleteTile(const vector2dst& position)
{
    log_assert(!tileEmpty(position), "You can only delete not empty tiles");

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

bool BoardModelComponent::changeTileData(const vector2dst& source,
                                         const BoardTileData& nv)
{
    log_assert(!tileEmpty(source),
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

bool BoardModelComponent::swapTileData(const vector2dst& lhs,
                                       const vector2dst& rhs)
{
    log_assert(!tileEmpty(lhs), "You can only change data in not empty tiles");
    log_assert(!tileEmpty(rhs), "You can only change data in not empty tiles");

    if (!tileEmpty(lhs) && !tileEmpty(rhs))
    {
        const BoardTileData temp{getTile(lhs)->value()};
        changeTileData(lhs, getTile(rhs)->value());
        changeTileData(rhs, temp);
        return true;
    }
    return false;
}

bool BoardModelComponent::moveTile(const vector2dst& source,
                                   const vector2dst& dest)
{
    if (!tileEmpty(source))
    {
        DisplayLog::info("Moving tile from ", source, " to ", dest);

        SITilePointer sourceTile{getTile(source)};
        SITilePointer destTile{getTile(dest)};

        if (sourceTile)
        {
            DisplayLog::info("Source Value: ", sourceTile->value());
            log_assert(!destTile, "Trying to move to a not empty tile: ", dest);

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
        }
    }
    else
    {
        DisplayLog::info("Trying to move empty tile: ", source.x, ",", source.y,
                         " ignoring it");
    }
    return false;
}

bool BoardModelComponent::validCoords(
    const vector2dst& tPosition) const noexcept
{
    return tiles_.size() > tPosition.x && tiles_[0U].size() > tPosition.y;
}

vector2dst BoardModelComponent::size() const noexcept
{
    return !tiles_.empty() ? vector2dst{tiles_.size(), tiles_[0U].size()}
                           : vector2dst{0U, 0U};
}

void BoardModelComponent::_setTile(const vector2dst& position,
                                   SITilePointer newTile)
{
    tiles_[position.x][position.y] = newTile;
}
}  // namespace haf::board
