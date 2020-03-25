#include <boardmanager/include/boardmodel.hpp>
#include <boardmanager/include/iboardmodelactuator.hpp>

#include <lib/include/liblog.hpp>

using namespace mtps;

namespace lib::board
{
BoardModelComponent::BoardModelComponent() = default;
BoardModelComponent::~BoardModelComponent() = default;

void BoardModelComponent::initialize(const vector2dst &size, IBoardModelActuator *boardModelActuator)
{
    DisplayLog::info("BoardModelComponent initialize with size: ", size);
    DisplayLog::info("IBoardModelActuator received ", boardModelActuator != nullptr);

    log_assert(m_actuator == nullptr, "m_actuator already contains a value");
    std::swap(m_actuator, boardModelActuator);
    _tiles.reserve(size.x);
    for (auto x = 0u; x < size.x; ++x)
    {
        _tiles.emplace_back(size.y);
        for (auto y = 0U; y < size.y; ++y)
        {
            _tiles[x].emplace_back();
        }
    }
    _tiles.shrink_to_fit();
}

SITilePointer BoardModelComponent::getTile(const vector2dst &position) const noexcept
{
    if (validCoords(position))
    {
        return _tiles[position.x][position.y];
    }

    DisplayLog::error("Error getting tile in coordinates ", position.x, ",", position.y);
    return SITilePointer();
}

void BoardModelComponent::setTile(const vector2dst &tPosition, SITilePointer newTile)
{
    log_assert(tileEmpty(tPosition), "You can only set data in empty tiles");

    _setTile(tPosition, newTile);
    newTile->tileAdded(tPosition);

    if (m_actuator)
    {
        m_actuator->tileAdded(tPosition, newTile);
    }
}

void BoardModelComponent::deleteTile(const vector2dst &position)
{
    log_assert(!tileEmpty(position), "You can only delete not empty tiles");

    SITilePointer current(getTile(position));
    current->tileRemoved(position);

    if (m_actuator)
    {
        m_actuator->tileRemoved(position, current);
    }
    _tiles[position.x][position.y].reset();
}

void BoardModelComponent::changeTileData(const vector2dst &source, const BoardTileData &nv)
{
    log_assert(!tileEmpty(source), "You can only change data in not empty tiles");

    auto tile(getTile(source));
    BoardTileData ov{tile->data.get()};

    if (m_actuator)
    {
        m_actuator->tileChanged(source, tile, ov, nv);
    }
    tile->tileChanged(source, ov, nv);
}

void BoardModelComponent::swapTileData(const vector2dst& lhs, const vector2dst& rhs)
{
    log_assert(!tileEmpty(lhs), "You can only change data in not empty tiles");
    log_assert(!tileEmpty(rhs), "You can only change data in not empty tiles");

    const BoardTileData temp{getTile(lhs)->data.get()};
    changeTileData(lhs, getTile(rhs)->data.get());
    changeTileData(rhs, temp);
}

bool BoardModelComponent::moveTile(const vector2dst &source, const vector2dst &dest)
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

            if (m_actuator)
            {
                m_actuator->tileMoved(source, dest, sourceTile);
            }
            sourceTile->tileMoved(source, dest);
            return true;
        }
    }
    else
    {
        DisplayLog::info("Trying to move empty tile: ", source.x, ",", source.y, " ignoring it");
    }
    return false;
}

void BoardModelComponent::_setTile(const vector2dst &position, SITilePointer newTile)
{
    _tiles[position.x][position.y] = newTile;
}
} // namespace lib::board
