#pragma once

#ifndef ZOPER_BOARDGROUP_HPP__
#define ZOPER_BOARDGROUP_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/scenenode.hpp>

#include "gamedata.hpp"
#include "boardscenenode.hpp"

using namespace lib;

namespace zoper
{
	class BoardGroup : public scene::nodes::TableNode<BoardSceneNode>
	{
	private:
		using BaseClass = scene::nodes::TableNode<BoardSceneNode>;
	public:
		BoardGroup(scene::SceneNode* parent, str name, sptr<GameData> gameData);
		virtual ~BoardGroup();

		void onCreated() override;
	private:
		sptr<GameData> m_gameData;
	};
}

#endif
