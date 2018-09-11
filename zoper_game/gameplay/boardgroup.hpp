#pragma once

#ifndef ZOPER_BOARDGROUP_HPP
#define ZOPER_BOARDGROUP_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenode.hpp>

#include "boardscenenode.hpp"

#include <lib/board/boardmodel.hpp>

namespace zoper
{
    using namespace lib;

    class BoardGroup : public scene::nodes::TableNode<BoardSceneNode>
	{
	private:
		using BaseClass = scene::nodes::TableNode<BoardSceneNode>;
	public:
		BoardGroup(scene::SceneNode* parent, str name, vector2dst size);
		virtual ~BoardGroup();

		void onCreated() override;

        sptr<board::BoardModelComponent> p_boardModel;

	};
}

#endif
