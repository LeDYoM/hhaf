#pragma once

#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>

#include "boardscenenode.hpp"

#include <lib/board/boardmodel.hpp>
#include <lib/board/iboardmodelactuator.hpp>

namespace zoper
{
    using namespace lib;

    class BoardGroup : public scene::nodes::TableNode<BoardSceneNode>, public board::IBoardModelActuator
    {
    private:
        using BaseClass = scene::nodes::TableNode<BoardSceneNode>;
    public:
        BoardGroup(scene::SceneNode* parent, str name, vector2dst size);
        ~BoardGroup() override;

        void onCreated() override;

        void tileRemoved(const vector2dst, board::SITilePointer) override;

        void setLevel(const size_type level);

        scene::Color getBackgroundTileColor(const size_type level, 
            vector2dst position, const bool isCenter) const;

        sptr<board::BoardModelComponent> p_boardModel;
        sptr<scene::SceneNode> m_mainBoardrg;
	};
}

#endif
