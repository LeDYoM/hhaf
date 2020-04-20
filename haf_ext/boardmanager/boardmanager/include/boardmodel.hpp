#pragma once

#ifndef HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP
#define HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/vector2d.hpp>
#include <haf/scene/include/icomponent.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardModelActuator;
using BackgroundData = mtps::s32;
using BackgroundFunction =
    mtps::function<BackgroundData(const mtps::vector2dst)>;

class BoardModelComponent : public haf::scene::IComponent
{
public:
    /**
     * @brief Method to initialize the component.
     * This method should be called once and only once per component.
     * Failing that is underfined behaviour.
     *
     * @param size Size of the board.
     * @param board_model_actuator Pointer to a @b IBoardModelActuator
     * to handle the callbacks.
     */
    void initialize(const mtps::vector2dst& size,
                    mtps::rptr<IBoardModelActuator> board_model_actuator);

    BackgroundFunction setBackgroundFunction(
        BackgroundFunction background_function);

    SITilePointer getTile(const mtps::vector2dst& position) const noexcept;
    bool tileEmpty(const mtps::vector2dst& position) const noexcept;
    bool setTile(const mtps::vector2dst& position, SITilePointer newTile);
    bool deleteTile(const mtps::vector2dst& position);
    bool moveTile(const mtps::vector2dst& source, const mtps::vector2dst& dest);
    bool changeTileData(const mtps::vector2dst& source,
                        const BoardTileData& nv);
    bool swapTileData(const mtps::vector2dst& lhs, const mtps::vector2dst& rhs);

    bool validCoords(const mtps::vector2dst& tPosition) const noexcept;
    BackgroundData backgroundType(
        const mtps::vector2dst& tPosition) const;
    mtps::vector2dst size() const noexcept;

    mtps::str toStr();

private:
    void _setTile(const mtps::vector2dst& position, SITilePointer newTile);

    BackgroundFunction background_function_{};
    mtps::rptr<IBoardModelActuator> actuator_{nullptr};
    mtps::vector<mtps::vector<SITilePointer>> tiles_;
};

}  // namespace haf::board

#endif
