#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/render/include/renderizable.hpp>
#include <boardmanager/include/itile.hpp>
#include "boardgroup.hpp"

namespace haf::board
{
class BoardManager;
}
namespace zoper
{

class GameBaseTile : public haf::board::ITile, public haf::scene::SceneNode
{
public:
    using TileBase = haf::board::ITile;

    GameBaseTile(mtps::rptr<haf::scene::SceneNode> const parent,
                 mtps::str name);
    ~GameBaseTile() override;

    haf::scene::Color getColorForToken() const;

    void tileChanged(const mtps::vector2dst& /*position */,
                     const haf::board::BoardTileData /* oldValue */,
                     const haf::board::BoardTileData /* newValue */) override;

    void tileAdded(const mtps::vector2dst& /* position */) override;

    void tileMoved(const mtps::vector2dst& /* source */,
                           const mtps::vector2dst& /* dest */) override;

    mtps::sptr<haf::board::BoardManager> getBoardManager();
    mtps::rptr<BoardGroup> getBoardGroup();

    bool isInCenter() const noexcept { return is_in_center; }
protected:
    mtps::sptr<haf::scene::Renderizable> node_;
private:
    bool is_in_center{false};
};
}  // namespace zoper

#endif