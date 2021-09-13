#ifndef ZOPER_TOKEN_HPP
#define ZOPER_TOKEN_HPP

#include "gamebasetile.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <boardmanager/include/itile.hpp>
#include <haf/include/animation/animation_component.hpp>

namespace zoper
{
/**
 * @brief This class represents one of the enemies in the board of the game.
 * The clas contains internal data like the token type inherited from
 * the base class. It also provides the required graphical information.
 */
class Token : public GameBaseTile
{
    using BaseClass = GameBaseTile;

public:
    using BoardTileData = GameBaseTile::BoardTileData;

    Token(htps::rptr<haf::scene::SceneNode> parent, htps::str name);
    ~Token() override;

    void setBox(const htps::Rectf32& box);

    static void resetTileCounter();

    bool canBeMoved(htps::vector2dst const& dest_position) const;
    void tileAdded(htps::vector2dst const& position) override;
    void tileRemoved(htps::vector2dst const& position) override;
    void tileChanged(htps::vector2dst const& position,
                     BoardTileData const oldValue,
                     BoardTileData const newValue) override;
    void tileMoved(htps::vector2dst const& source,
                   htps::vector2dst const& dest) override;

private:
    static htps::u32 tile_counter_;
    htps::vector2df board2SceneFactor_;
    htps::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif