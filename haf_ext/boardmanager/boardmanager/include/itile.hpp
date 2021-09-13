#ifndef HAF_BOARD_ITILE_HPP
#define HAF_BOARD_ITILE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

namespace haf::board
{

class ITile
{
public:
    using BoardTileData = htps::s32;

    constexpr ITile() noexcept {}
    virtual ~ITile() {}

    virtual bool canBeMoved(htps::vector2dst const&) const { return true; }
    virtual void tileAdded(htps::vector2dst const& /* position */) {}
    virtual void tileRemoved(htps::vector2dst const& /* position */) {}
    virtual void tileChanged(htps::vector2dst const& /*position */,
                             BoardTileData const /* oldValue */,
                             BoardTileData const /* newValue */)
    {}

    virtual void tileMoved(htps::vector2dst const& /* source */,
                           htps::vector2dst const& /* dest */)
    {}

    BoardTileData value() const noexcept { return data_; }

private:
    BoardTileData data_{static_cast<BoardTileData>(0)};
    friend class BoardManager;
};

using SITilePointer = htps::sptr<ITile>;
}  // namespace haf::board

#endif
