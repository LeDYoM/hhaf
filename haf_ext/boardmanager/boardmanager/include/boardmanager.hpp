#ifndef HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP
#define HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/component/component.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardManagerActuator;

class BoardManager : public haf::component::Component
{
public:
    using BackgroundData = htps::s32;
    using BoardTileData  = ITile::BoardTileData;

    using BackgroundFunction =
        htps::function<BackgroundData(htps::vector2dst const&)>;

    /**
     * @brief Method to initialize the component.
     * This method should be called once and only once per component.
     * Failing that is underfined behaviour.
     *
     * @param size Size of the board in cells
     * @param board_manager_actuator Pointer to a @b IBoardManagerActuator
     * to handle the callbacks.
     */
    void initialize(htps::vector2dst const& size,
                    htps::rptr<IBoardManagerActuator> board_manager_actuator);

    BackgroundFunction setBackgroundFunction(
        BackgroundFunction background_function);

    SITilePointer getTile(htps::vector2dst const& position) const noexcept;
    bool tileEmpty(htps::vector2dst const& position) const noexcept;
    bool setTile(htps::vector2dst const& position, SITilePointer newTile);
    bool deleteTile(htps::vector2dst const& position);
    bool moveTile(htps::vector2dst const& source, htps::vector2dst const& dest);
    bool changeTileData(htps::vector2dst const& source,
                        BoardTileData const& nv);
    bool swapTileData(htps::vector2dst const& lhs, htps::vector2dst const& rhs);

    bool validCoords(const htps::vector2dst& tPosition) const noexcept;
    BackgroundData backgroundData(const htps::vector2dst& tPosition) const;
    htps::vector2dst size() const noexcept;

    htps::str toStr();

private:
    void initializeTileMatrix(htps::vector2dst const& size);
    void _setTile(const htps::vector2dst& position, SITilePointer newTile);

    BackgroundFunction background_function_{};
    htps::rptr<IBoardManagerActuator> actuator_{nullptr};
    htps::vector<htps::vector<SITilePointer>> tiles_;
};

}  // namespace haf::board

#endif
