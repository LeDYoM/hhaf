#pragma once

#ifndef HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP
#define HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "itile.hpp"
#include <lib/scene/include/icomponent.hpp>

namespace lib::board
{
class IBoardModelActuator;

class BoardModelComponent : public scene::IComponent
{
public:
    BoardModelComponent();
    ~BoardModelComponent() override;

    void initialize(const mtps::vector2dst& size,
                    mtps::rptr<IBoardModelActuator> board_model_actuator);

    SITilePointer getTile(const mtps::vector2dst& position) const noexcept;
    bool tileEmpty(const mtps::vector2dst& position) const noexcept;
    void setTile(const mtps::vector2dst& position, SITilePointer newTile);
    void deleteTile(const mtps::vector2dst& position);
    bool moveTile(const mtps::vector2dst& source, const mtps::vector2dst& dest);
    void changeTileData(const mtps::vector2dst& source,
                        const BoardTileData& nv);
    void swapTileData(const mtps::vector2dst& lhs, const mtps::vector2dst& rhs);

    bool validCoords(const mtps::vector2dst& tPosition) const noexcept;
    mtps::vector2dst size() const noexcept;

private:
    void _setTile(const mtps::vector2dst& position, SITilePointer newTile);

    mtps::rptr<IBoardModelActuator> actuator_{nullptr};
    mtps::vector<mtps::vector<SITilePointer>> tiles_;
};
}  // namespace lib::board

#endif
