#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <htypes/include/vector2d.hpp>
#include <htypes/include/connection.hpp>

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/tablenode.hpp>
#include <haf/scene_nodes/include/tablenode_properties.hpp>

#include "boardtilescenenode.hpp"
#include "direction.hpp"

#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/iboardmanageractuator.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{

class LevelProperties;
class Player;

class BoardGroup : public haf::scene::nodes::TableNode<BoardTileSceneNode>,
                   public haf::board::IBoardManagerActuator
{
private:
    using BaseClass = haf::scene::nodes::TableNode<BoardTileSceneNode>;
    using BaseClass::prop;    
public:
    using BaseClass::BaseClass;

    ~BoardGroup() override;

    void configure(mtps::vector2dst size,
                   mtps::sptr<LevelProperties> level_properties);
    void createNewToken(const haf::board::BoardTileData data,
                        const mtps::vector2dst& board_position,
                        const mtps::vector2df& size);

    void tileRemoved(const mtps::vector2dst,
                     haf::board::SITilePointer&) override;
    void setLevel(const mtps::size_type level);

    haf::scene::Color getBackgroundTileColor(const mtps::size_type level,
                                             mtps::vector2dst position,
                                             const bool isCenter) const;

    /**
     * @brief Move a tile from its current position towards the center in a
     * given direction.
     *
     * @param direction Direction to move the tile to
     * @param position Position where the tile currently is.
     * @return true The tile reached the center
     * @return false The tile is not in the center
     */
    bool moveTileInDirection(Direction const direction,
                             mtps::vector2dst const position);

    bool moveTowardsCenter(Direction const direction,
                           mtps::vector2dst const& position);

    mtps::sptr<haf::board::BoardManager> boardManager() noexcept;
    const mtps::sptr<const haf::board::BoardManager> boardManager() const noexcept;
    mtps::sptr<haf::scene::SceneNode> tokensSceneNode() noexcept;
    const mtps::sptr<haf::scene::SceneNode> tokensSceneNode() const noexcept;
    mtps::sptr<Player> player() noexcept;
    const mtps::sptr<Player> player() const noexcept;

    mtps::vector2df board2SceneFactor() const;
    mtps::vector2df board2Scene(const mtps::vector2dst& bPosition) const;
    mtps::vector2df tileSize() const;

    void launchPlayer();

    mtps::emitter<mtps::vector2dst const> token_hit;

private:
    mtps::sptr<Player> player_;
    mtps::sptr<haf::scene::SceneNode> tokens_scene_node;
    mtps::sptr<LevelProperties> level_properties_;

    void addPlayer();
};
}  // namespace zoper

#endif
