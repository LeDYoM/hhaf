#ifndef ZOPER_TOKEN_HPP
#define ZOPER_TOKEN_HPP

#include "gamebasetile.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

#include <boardmanager/include/itile.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>

namespace zoper
{
/**
 * @brief This class represents one of the enemies in the board of the game.
 * The clas contains internal data like the token type inherited from
 * the base class. It also provides the required graphical information.
 */
class Token : public GameBaseTile
{
public:
    using BaseClass = GameBaseTile;

    Token(mtps::rptr<haf::scene::SceneNode> parent, mtps::str name);
    ~Token() override;

    void setBoxBoundaries(const mtps::Rectf32 &box);

    static void resetTileCounter();

    bool canBeMoved(mtps::vector2dst const& dest_position) const;
    void tileAdded(const mtps::vector2dst &position) override;
    void tileRemoved(const mtps::vector2dst & position) override;
    void tileChanged(const mtps::vector2dst & position,
                     const haf::board::BoardTileData oldValue,
                     const haf::board::BoardTileData newValue) override;
    void tileMoved(const mtps::vector2dst &source,
                   const mtps::vector2dst &dest) override;

private:
    static mtps::u32 m_tileCounter;
    mtps::vector2df board2SceneFactor_;
    mtps::sptr<haf::scene::AnimationComponent> animation_component_;
};
} // namespace zoper

#endif