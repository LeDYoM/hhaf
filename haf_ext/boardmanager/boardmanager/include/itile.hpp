#pragma once

#ifndef HAF_BOARD_ITILE_HPP
#define HAF_BOARD_ITILE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace haf::board
{
using BoardTileData = mtps::s32;

class ITile
{
public:
    constexpr ITile() noexcept {}
    virtual ~ITile() {}

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
    friend class BoardModelComponent;

};

using SITilePointer = mtps::sptr<ITile>;
}  // namespace haf::board

#endif
