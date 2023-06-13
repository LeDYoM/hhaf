#ifndef HAF_BOARD_IBOARDMANAGER_ACTUATOR_HPP
#define HAF_BOARD_IBOARDMANAGER_ACTUATOR_HPP

#include <htypes/include/types.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardManagerActuator
{
public:
    using BoardTileData = ITile::BoardTileData;

    virtual void tileAdded(const fmath::vector2dst, SITilePointer&) {}
    virtual void tileRemoved(const fmath::vector2dst, SITilePointer&) {}
    virtual void tileMoved(const fmath::vector2dst,
                           const fmath::vector2dst,
                           SITilePointer&)
    {}
    virtual void tileChanged(const fmath::vector2dst,
                             SITilePointer&,
                             const BoardTileData,
                             const BoardTileData)
    {}
};
}  // namespace haf::board

#endif
