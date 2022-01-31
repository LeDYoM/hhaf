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
    using BoardTileData = types::s32;
    using BoardPositionType = BoardPositionType;

    constexpr ITile() noexcept = default;
    virtual ~ITile() = default;

    virtual bool canBeMoved(BoardPositionType const&) const { return true; }
    virtual void tileAdded(BoardPositionType const& /* position */) {}
    virtual void tileRemoved(BoardPositionType const& /* position */) {}
    virtual void tileChanged(BoardPositionType const& /*position */,
                             BoardTileData const /* oldValue */,
                             BoardTileData const /* newValue */)
    {}

    virtual void tileMoved(BoardPositionType const& /* source */,
                           BoardPositionType const& /* dest */)
    {}

    BoardTileData value() const noexcept { return data_; }

private:
    BoardTileData data_{static_cast<BoardTileData>(0)};
    friend class BoardManager;
};

using SITilePointer = htps::sptr<ITile>;
}  // namespace haf::board

#endif
