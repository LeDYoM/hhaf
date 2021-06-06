#ifndef HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP
#define HEF_EXT_BOARDMANAGER_BOARDMODEL_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/icomponent.hpp>
#include "itile.hpp"

namespace haf::board
{
class IBoardManagerActuator;
using BackgroundData = htps::s32;
using BackgroundFunction =
    htps::function<BackgroundData(const htps::vector2dst&)>;

class BoardManager : public haf::scene::IComponent
{
public:
    /**
     * @brief Method to initialize the component.
     * This method should be called once and only once per component.
     * Failing that is underfined behaviour.
     *
     * @param size Size of the board.
     * @param board_manager_actuator Pointer to a @b IBoardManagerActuator
     * to handle the callbacks.
     */
    void initialize(const htps::vector2dst& size,
                    htps::rptr<IBoardManagerActuator> board_manager_actuator);

    BackgroundFunction setBackgroundFunction(
        BackgroundFunction background_function);

    SITilePointer getTile(const htps::vector2dst& position) const noexcept;
    bool tileEmpty(const htps::vector2dst& position) const noexcept;
    bool setTile(const htps::vector2dst& position, SITilePointer newTile);
    bool deleteTile(const htps::vector2dst& position);
    bool moveTile(const htps::vector2dst& source, const htps::vector2dst& dest);
    bool changeTileData(const htps::vector2dst& source,
                        const BoardTileData& nv);
    bool swapTileData(const htps::vector2dst& lhs, const htps::vector2dst& rhs);

    bool validCoords(const htps::vector2dst& tPosition) const noexcept;
    BackgroundData backgroundType(
        const htps::vector2dst& tPosition) const;
    htps::vector2dst size() const noexcept;

    htps::str toStr();

private:
    void _setTile(const htps::vector2dst& position, SITilePointer newTile);

    BackgroundFunction background_function_{};
    htps::rptr<IBoardManagerActuator> actuator_{nullptr};
    htps::vector<htps::vector<SITilePointer>> tiles_;
};

}  // namespace haf::board

#endif
