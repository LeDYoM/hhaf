#ifndef HAF_BOARD_ITILE_HPP
#define HAF_BOARD_ITILE_HPP

#include <haf/include/types/basic_types.hpp>
#include <htypes/include/vector2d.hpp>

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
    using BoardPosition_t = htps::vector2dst;

    constexpr ITile() noexcept = default;
    virtual ~ITile() = default;

    virtual bool canBeMoved(BoardPosition_t const&) const { return true; }
    virtual void tileAdded(BoardPosition_t const& /* position */) {}
    virtual void tileRemoved(BoardPosition_t const& /* position */) {}
    virtual void tileChanged(BoardPosition_t const& /*position */,
                             BoardTileData const /* oldValue */,
                             BoardTileData const /* newValue */)
    {}

    virtual void tileMoved(BoardPosition_t const& /* source */,
                           BoardPosition_t const& /* dest */)
    {}

    BoardTileData value() const noexcept { return data_; }

private:
    BoardTileData data_{static_cast<BoardTileData>(0)};
    friend class BoardManager;
};

using SITilePointer = htps::sptr<ITile>;
}  // namespace haf::board

#endif
