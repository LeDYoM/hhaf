#ifndef HAF_BOARD_ITILE_HPP
#define HAF_BOARD_ITILE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::board
{
using BoardTileData = htps::s32;

class ITile
{
public:
    constexpr ITile() noexcept {}
    virtual ~ITile() {}

    virtual bool canBeMoved(htps::vector2dst const&) const { return true; }
    virtual void tileAdded(const htps::vector2dst& /* position */) {}
    virtual void tileRemoved(const htps::vector2dst& /* position */) {}
    virtual void tileChanged(const htps::vector2dst& /*position */,
                             const BoardTileData /* oldValue */,
                             const BoardTileData /* newValue */)
    {}

    virtual void tileMoved(const htps::vector2dst& /* source */,
                           const htps::vector2dst& /* dest */)
    {}

    BoardTileData value() const noexcept { return data_; }

private:
    BoardTileData data_{0};
    friend class BoardManager;

};

using SITilePointer = htps::sptr<ITile>;
}  // namespace haf::board

#endif
