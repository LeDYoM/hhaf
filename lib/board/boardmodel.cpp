#include "boardmodel.hpp"
#include "iboardmodelactuator.hpp"
#include <lib/include/liblog.hpp>

namespace lib::board
{
    BoardModelComponent::BoardModelComponent() = default;
    BoardModelComponent::~BoardModelComponent() = default;

    void BoardModelComponent::initialize(const vector2dst &size, IBoardModelActuator* boardModelActuator)
    {
        log_debug_info("BoardModelComponent initialize with size: ", size);
        log_debug_info("IBoardModelActuator received ", boardModelActuator != nullptr);

        assert_release(m_actuator == nullptr, "m_actuator already contains a value");
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

        log_debug_error("Error getting tile in coordinates ", position.x, ",", position.y);
        return SITilePointer();
    }

    void BoardModelComponent::setTile(const lib::vector2dst &tPosition, SITilePointer newTile)
    {
        assert_release(tileEmpty(tPosition), "You can only set data in empty tiles");

        _setTile(tPosition, newTile);
        newTile->tileAdded(tPosition);

        if (m_actuator)
        {
            m_actuator->tileAdded(tPosition, newTile);
        }
    }

    void BoardModelComponent::deleteTile(const vector2dst &position)
    {
        assert_release(!tileEmpty(position), "You can only delete not empty tiles");

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
        assert_release(!tileEmpty(source), "You can only change data in not empty tiles");

        auto tile (getTile(source));
        BoardTileData ov{ tile->get() };

        if (m_actuator)
        {
            m_actuator->tileChanged(source, tile, ov, nv);
        }
        tile->tileChanged(source, ov, nv);
    }

    bool BoardModelComponent::moveTile(const vector2dst &source, const vector2dst &dest)
    {
        if (!tileEmpty(source))
        {
            log_debug_info("Moving tile from ", source, " to ", dest);

            SITilePointer sourceTile{ getTile(source) };
            SITilePointer destTile{ getTile(dest) };

            log_debug_info("Source Value: ", sourceTile->get());

            if (sourceTile)
            {
                assert_release(!destTile, "Trying to move to a not empty tile: " , dest);

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
            log_debug_info("Trying to move empty tile: ", source.x , ",", source.y, " ignoring it");
        }
        return false;
    }

    void BoardModelComponent::_setTile(const vector2dst &position, SITilePointer newTile)
    {
        _tiles[position.x][position.y] = newTile;
    }
}
