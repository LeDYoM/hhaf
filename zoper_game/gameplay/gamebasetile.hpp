#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/scene/color.hpp>
#include <boardmanager/include/itile.hpp>
#include "boardgroup.hpp"

namespace haf::board
{
class BoardManager;
}

namespace zoper
{

class GameBaseTile : public haf::board::ITile,
                     public haf::scene::TransformableSceneNode
{
    using BaseClass = haf::scene::TransformableSceneNode;

protected:
    using TileBase = haf::board::ITile;

public:
    using BoardPositionType = TileBase::BoardPositionType;
    using BoardTileData = haf::board::ITile::BoardTileData;

    GameBaseTile(htps::rptr<haf::scene::SceneNode> const parent,
                 htps::str name);
    ~GameBaseTile() override;

    void tileChanged(BoardTileData const oldValue,
                     BoardTileData const newValue) override;

    void tileAdded() override;

    void tileMoved(BoardPositionType const& dest) override;

    bool isInCenter() const noexcept;

protected:
    haf::scene::Color getColorForToken() const;

    htps::sptr<haf::board::BoardManager> getBoardManager();
    htps::sptr<haf::board::BoardManager const> const getBoardManager() const;
    htps::rptr<BoardGroup> getBoardGroup();
    htps::rptr<BoardGroup const> getBoardGroup() const;

    htps::vector2df board2SceneFactor() const;
    htps::vector2df board2Scene(const htps::vector2dst& bPosition) const;
    htps::vector2df tileSize() const;

private:
    bool is_in_center{false};
    virtual void setTokenColor(haf::scene::Color const& token_color) = 0;
};
}  // namespace zoper

#endif