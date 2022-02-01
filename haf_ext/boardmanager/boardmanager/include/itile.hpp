#ifndef HAF_BOARD_ITILE_HPP
#define HAF_BOARD_ITILE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/scene_types.hpp>
#include <htypes/include/vector2d.hpp>
#include <boardmanager/include/board_types.hpp>

namespace haf::board
{
/**
 * @brief Interface class for all tiles in the board.
 * It provides methods to be notified when tiles are added, removed or moved
 */
class ITile
{
public:
    using BoardTileData     = types::s32;
    using BoardPositionType = BoardPositionType;

    constexpr ITile() noexcept = default;
    virtual ~ITile()           = default;

    virtual bool canBeMovedTo(BoardPositionType const&) const { return true; }
    virtual void tileAdded() {}
    virtual void tileRemoved() {}
    virtual void tileChanged(BoardTileData const /* oldValue */,
                             BoardTileData const /* newValue */)
    {}

    virtual void tileMoved(BoardPositionType const& /* source */)
    {}

    constexpr BoardTileData value() const noexcept { return data_; }
    constexpr BoardPositionType const& boardPosition() const noexcept
    {
        return board_position;
    }

private:
    BoardTileData data_{static_cast<BoardTileData>(0)};
    BoardPositionType board_position{};
    friend class BoardManager;
};

using SITilePointer = htps::sptr<ITile>;
}  // namespace haf::board

#endif
