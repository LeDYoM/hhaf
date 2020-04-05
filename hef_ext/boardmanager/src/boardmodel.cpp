#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>

#include <lib/include/liblog.hpp>

using namespace mtps;

namespace haf::board
{
BoardModelComponent::BoardModelComponent()  = default;
BoardModelComponent::~BoardModelComponent() = default;

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

    DisplayLog::error("Error getting tile in coordinates ", position.x, ",",
                      position.y);
    return SITilePointer();
}

void BoardModelComponent::setTile(const vector2dst& tPosition,
                                  SITilePointer newTile)
{
    log_assert(tileEmpty(tPosition), "You can only set data in empty tiles");

    _setTile(tPosition, newTile);
    newTile->tileAdded(tPosition);

    if (actuator_)
    {
        actuator_->tileAdded(tPosition, newTile);
    }
}

bool BoardModelComponent::tileEmpty(const vector2dst& position) const noexcept
{
    return getTile(position) == nullptr;
}

void BoardModelComponent::deleteTile(const vector2dst& position)
{
    log_assert(!tileEmpty(position), "You can only delete not empty tiles");

    SITilePointer current(getTile(position));
    current->tileRemoved(position);

    if (actuator_)
    {
        actuator_->tileRemoved(position, current);
    }
    tiles_[position.x][position.y].reset();
}

void BoardModelComponent::changeTileData(const vector2dst& source,
                                         const BoardTileData& nv)
{
    log_assert(!tileEmpty(source),
               "You can only change data in not empty tiles");

    auto tile(getTile(source));
    BoardTileData ov{tile->data.get()};

    if (actuator_)
    {
        actuator_->tileChanged(source, tile, ov, nv);
    }
    tile->tileChanged(source, ov, nv);
}

void BoardModelComponent::swapTileData(const vector2dst& lhs,
                                       const vector2dst& rhs)
{
    log_assert(!tileEmpty(lhs), "You can only change data in not empty tiles");
    log_assert(!tileEmpty(rhs), "You can only change data in not empty tiles");

    const BoardTileData temp{getTile(lhs)->data.get()};
    changeTileData(lhs, getTile(rhs)->data.get());
    changeTileData(rhs, temp);
}

bool BoardModelComponent::moveTile(const vector2dst& source,
                                   const vector2dst& dest)
{
    if (!tileEmpty(source))
    {
        DisplayLog::info("Moving tile from ", source, " to ", dest);

        SITilePointer sourceTile{getTile(source)};
        SITilePointer destTile{getTile(dest)};

        DisplayLog::info("Source Value: ", sourceTile->data.get());

        if (sourceTile)
        {
            log_assert(!destTile, "Trying to move to a not empty tile: ", dest);

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
    return vector2dst{tiles_.size(), tiles_[0].size()};
}

void BoardModelComponent::_setTile(const vector2dst& position,
                                   SITilePointer newTile)
{
    tiles_[position.x][position.y] = newTile;
}
}  // namespace haf::board