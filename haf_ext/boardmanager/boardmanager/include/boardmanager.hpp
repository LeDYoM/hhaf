#ifndef HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP
#define HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/str.hpp>
#include <facil_math/include/vector2d.hpp>
#include <haf/include/component/component.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardManagerActuator;
/**
 * @brief Component to manage a board of tiles.
 * This component implements a way to manage a group of tiles in a 2D matrix
 * providing functionality to add, remove and check for data.
 */
class BoardManager : public haf::component::Component
{
public:
    using BackgroundData    = htps::s32;
    using BoardTileData     = ITile::BoardTileData;

    using BackgroundFunction =
        htps::function<BackgroundData(fmath::vector2dst const&)>;

    /**
     * @brief Method to initialize the component.
     * This method should be called once and only once per component.
     * Failing that is underfined behaviour.
     *
     * @param size Size of the board in cells
     * @param board_manager_actuator Pointer to a @b IBoardManagerActuator
     * to handle the callbacks.
     */
    void initialize(fmath::vector2dst const& size,
                    htps::rptr<IBoardManagerActuator> board_manager_actuator);

    BackgroundFunction setBackgroundFunction(
        BackgroundFunction background_function);

    SITilePointer getTile(BoardPositionType const& position) const noexcept;
    bool tileEmpty(BoardPositionType const& position) const noexcept;
    bool setTile(BoardPositionType const& position, SITilePointer newTile);
    bool deleteTile(BoardPositionType const& position);
    bool moveTile(BoardPositionType const source, BoardPositionType const dest);
    bool changeTileData(BoardPositionType const& source,
                        BoardTileData const& new_value);
    bool swapTileData(BoardPositionType const& lhs,
                      BoardPositionType const& rhs);

    bool validCoords(BoardPositionType const& tPosition) const noexcept;
    BackgroundData backgroundData(BoardPositionType const& tPosition) const;
    fmath::vector2dst size() const noexcept;

    htps::str toStr();

private:
    void initializeTileMatrix(fmath::vector2dst const& size);
    void _setTile(const fmath::vector2dst& position, SITilePointer newTile);

    BackgroundFunction background_function_{};
    htps::rptr<IBoardManagerActuator> actuator_{nullptr};
    htps::vector<htps::vector<SITilePointer>> tiles_;
};

}  // namespace haf::board

#endif
