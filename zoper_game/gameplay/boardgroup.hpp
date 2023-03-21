#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <htypes/include/vector2d.hpp>
#include <haf/include/events/connection.hpp>

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/table_component.hpp>

#include "boardtilescene_node.hpp"
#include "direction.hpp"

#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/iboardmanageractuator.hpp>
#include <boardmanager/include/itile.hpp>

namespace zoper
{

class LevelProperties;
class Player;

class BoardGroup : public haf::scene::TableNode<BoardTileSceneNode>,
                   public haf::board::IBoardManagerActuator
{

private:
    using BaseClass = haf::scene::TableNode<BoardTileSceneNode>;

public:
    using BoardTileData = haf::board::IBoardManagerActuator::BoardTileData;
    using BaseClass::BaseClass;

    constexpr static char const StaticName[] = "BoardGroup";

    ~BoardGroup() override;

    void configure(htps::vector2dst size,
                   htps::sptr<LevelProperties> level_properties);

    void onAttached() override;

    void createNewToken(BoardTileData const data,
                        htps::vector2dst const& board_position);

    void tileRemoved(const htps::vector2dst,
                     haf::board::SITilePointer&) override;
    void setLevel(const htps::size_type level);

    haf::scene::Color getBackgroundTileColor(const htps::size_type level,
                                             htps::vector2dst position,
                                             const bool isCenter) const;

    void movePlayer(Direction const& direction);

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
                             htps::vector2dst const position);

    bool moveTowardsCenter(Direction const direction,
                           htps::vector2dst const position);

    htps::sptr<haf::board::BoardManager> boardManager() noexcept;
    const htps::sptr<const haf::board::BoardManager> boardManager()
        const noexcept;
    htps::sptr<haf::scene::SceneNode> tokensSceneNode() noexcept;
    const htps::sptr<haf::scene::SceneNode> tokensSceneNode() const noexcept;
    htps::sptr<Player> player() noexcept;
    const htps::sptr<Player> player() const noexcept;

    htps::vector2df board2SceneFactor() const;
    htps::vector2df board2Scene(const htps::vector2dst& bPosition) const;
    htps::vector2df tileSize() const;

private:
    void onTableNodeAdded(htps::sptr<haf::scene::SceneNode> const&);
    htps::sptr<Player> player_;
    htps::sptr<haf::scene::TransformableSceneNode> tokens_scene_node;
    htps::sptr<LevelProperties> level_properties_;

    void addPlayer();
};
}  // namespace zoper

#endif
