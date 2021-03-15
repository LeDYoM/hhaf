#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
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

    GameBaseTile(htps::rptr<haf::scene::SceneNode> const parent,
                 htps::str name);
    ~GameBaseTile() override;

    haf::scene::Color getColorForToken() const;

    void tileChanged(const htps::vector2dst& /*position */,
                     const haf::board::BoardTileData /* oldValue */,
                     const haf::board::BoardTileData /* newValue */) override;

    void tileAdded(const htps::vector2dst& /* position */) override;

    void tileMoved(const htps::vector2dst& /* source */,
                           const htps::vector2dst& /* dest */) override;

    htps::sptr<haf::board::BoardManager> getBoardManager();
    htps::sptr<haf::board::BoardManager const> const getBoardManager() const;
    htps::rptr<BoardGroup> getBoardGroup();
    htps::rptr<BoardGroup const> getBoardGroup() const;

    bool isInCenter() const noexcept { return is_in_center; }

protected:
    htps::vector2df board2SceneFactor() const;
    htps::vector2df board2Scene(const htps::vector2dst& bPosition) const;
    htps::vector2df tileSize() const;

    htps::sptr<haf::scene::Renderizable> node_;
private:
    bool is_in_center{false};
};
}  // namespace zoper

#endif