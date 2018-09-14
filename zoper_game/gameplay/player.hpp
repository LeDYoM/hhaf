#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "gamebasetile.hpp"
#include "direction.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/board/boardmodel.hpp>

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
        PropertyTrigger<Direction> currentDirection;

        void movePlayer(const Direction &direction, const lib::function<bool(const lib::vector2dst&)> &pointInCenter, const lib::sptr<lib::board::BoardModelComponent> &boardModel);
        void updateDirection();
        void updateDirectionFromParameter(const Direction destDirection);

        void launchAnimation(vector2df toWhere);

        void tileAdded(const vector2dst &position) override;
        void tileRemoved(const vector2dst & /* position */) override {}
        void tileChanged(const vector2dst & /*position */,
            const board::BoardTileData /* oldValue */,
            const board::BoardTileData /* newValue */) override {}
        void tileMoved(const vector2dst& /* source */,
            const vector2dst& /* dest */) override {}

    private:
        void launchAnimationBack(vector2df toWhere);
        scene::SceneNodeSPtr m_extraSceneNode;
        scene::SceneNodeSPtr m_extraSceneNode_2;
        vector2df m_board2SceneFactor;
    };
}

#endif
