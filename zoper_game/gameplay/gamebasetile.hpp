#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/render/renderizable.hpp>
#include <boardmanager/include/itile.hpp>
#include "boardgroup.hpp"

namespace haf::board
{
class BoardManager;
}

namespace zoper
{

class GameBaseTile : public haf::board::ITile,
                     public haf::scene::RenderizableSceneNode
{

    using BaseClass = haf::scene::RenderizableSceneNode;

protected:
    using TileBase = haf::board::ITile;

public:
    using BoardTileData = haf::board::ITile::BoardTileData;

    GameBaseTile(htps::rptr<haf::scene::SceneNode> const parent,
                 htps::str name);
    ~GameBaseTile() override;

    haf::scene::Color getColorForToken() const;

    void tileChanged(htps::vector2dst const& position,
                     BoardTileData const oldValue,
                     BoardTileData const newValue) override;

    void tileAdded(htps::vector2dst const& position) override;

    void tileMoved(htps::vector2dst const& source,
                   htps::vector2dst const& dest) override;

    htps::sptr<haf::board::BoardManager> getBoardManager();
    htps::sptr<haf::board::BoardManager const> const getBoardManager() const;
    htps::rptr<BoardGroup> getBoardGroup();
    htps::rptr<BoardGroup const> getBoardGroup() const;

    bool isInCenter() const noexcept { return is_in_center; }

protected:
    htps::vector2df board2SceneFactor() const;
    htps::vector2df board2Scene(const htps::vector2dst& bPosition) const;
    htps::vector2df tileSize() const;

private:
    bool is_in_center{false};
};
}  // namespace zoper

#endif