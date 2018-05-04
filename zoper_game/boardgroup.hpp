#pragma once

#ifndef ZOPER_BOARDGROUP_HPP__
#define ZOPER_BOARDGROUP_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenode.hpp>

#include "boardscenenode.hpp"

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
	};
}

#endif
