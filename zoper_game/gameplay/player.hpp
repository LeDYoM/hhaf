#ifndef ZOPER_PLAYER_INCLUDE_HPP
#define ZOPER_PLAYER_INCLUDE_HPP

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/board/boardmodel.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>

namespace zoper
{
    using namespace lib;
    class Player : public GameBaseTile
    {
    public:
        Player(scene::SceneNode* const parent, const str &name,
               vector2dst bPosition, Rectf32 box, vector2df board2SceneFactor);
        virtual ~Player();

        PropertyTrigger<vector2dst> boardPosition;
        BasicProperty<Direction> currentDirection;

        void movePlayer(const Direction &direction, const sptr<board::BoardModelComponent> &boardModel);
        void updateDirectionFromParameter(const Direction destDirection);

        void launchAnimation(vector2df toWhere);

        void tileAdded(const vector2dst &position) override;
        void tileRemoved(const vector2dst & /* position */) override {}
        void tileChanged(const vector2dst & position,
            const board::BoardTileData oldValue,
            const board::BoardTileData newValue) override;
        void tileMoved(const vector2dst& source,
            const vector2dst& dest) override;

    private:
        void launchAnimationBack(vector2df toWhere);
        sptr<scene::AnimationComponent> animation_component_;
        scene::SceneNodeSPtr m_extraSceneNode;
        scene::SceneNodeSPtr m_extraSceneNode_2;
        vector2df m_board2SceneFactor;
    };
}

#endif
