#ifndef ZOPER_TOKEN_HPP
#define ZOPER_TOKEN_HPP

#include "gamebasetile.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>

#include <boardmanager/include/itile.hpp>
#include <haf/include/scene_components/animationcomponent.hpp>

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
    void tileAdded(const htps::vector2dst& position) override;
    void tileRemoved(const htps::vector2dst& position) override;
    void tileChanged(const htps::vector2dst& position,
                     const BoardTileData oldValue,
                     const BoardTileData newValue) override;
    void tileMoved(const htps::vector2dst& source,
                   const htps::vector2dst& dest) override;

private:
    static htps::u32 m_tileCounter;
    htps::vector2df board2SceneFactor_;
    htps::sptr<haf::scene::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif