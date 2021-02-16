#ifndef HAF_BOARD_ITILE_HPP
#define HAF_BOARD_ITILE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::board
{
using BoardTileData = mtps::s32;

class ITile
{
public:
    constexpr ITile() noexcept {}
    virtual ~ITile() {}

    virtual bool canBeMoved(mtps::vector2dst const&) const { return true; }
    virtual void tileAdded(const mtps::vector2dst& /* position */) {}
    virtual void tileRemoved(const mtps::vector2dst& /* position */) {}
    virtual void tileChanged(const mtps::vector2dst& /*position */,
                             const BoardTileData /* oldValue */,
                             const BoardTileData /* newValue */)
    {}

    virtual void tileMoved(const mtps::vector2dst& /* source */,
                           const mtps::vector2dst& /* dest */)
    {}

    BoardTileData value() const noexcept { return data_; }

private:
    BoardTileData data_{0};
    friend class BoardManager;

};

using SITilePointer = mtps::sptr<ITile>;
}  // namespace haf::board

#endif
