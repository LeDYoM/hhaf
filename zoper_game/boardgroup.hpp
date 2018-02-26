#pragma once

#ifndef ZOPER_BOARDGROUP_HPP__
#define ZOPER_BOARDGROUP_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenode.hpp>

#include "gamedata.hpp"

using namespace lib;

namespace zoper
{
	class BoardGroup : public scene::nodes::TableNode<scene::SceneNode>
	{
	private:
		using BaseClass = scene::nodes::TableNode<scene::SceneNode>;
	public:
		BoardGroup(scene::SceneNode* parent, str name, sptr<GameData> gameData);
		virtual ~BoardGroup();

		void onCreated() override;
	private:
		sptr<GameData> m_gameData;
	};
}

#endif
