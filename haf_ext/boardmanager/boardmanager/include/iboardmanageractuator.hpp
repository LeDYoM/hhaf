#ifndef HAF_BOARD_IBOARDMANAGER_ACTUATOR_HPP
#define HAF_BOARD_IBOARDMANAGER_ACTUATOR_HPP

#include <htypes/include/types.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardManagerActuator
{
public:
    virtual void tileAdded(const htps::vector2dst, SITilePointer&) {}
    virtual void tileRemoved(const htps::vector2dst, SITilePointer&) {}
    virtual void tileMoved(const htps::vector2dst,
                           const htps::vector2dst,
                           SITilePointer&)
    {}
    virtual void tileChanged(const htps::vector2dst,
                             SITilePointer&,
                             const BoardTileData,
                             const BoardTileData)
    {}
};
}  // namespace haf::board

#endif
