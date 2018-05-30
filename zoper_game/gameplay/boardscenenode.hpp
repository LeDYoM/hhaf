#pragma once

#ifndef ZOPER_BOARDSCENENODE_INCLUDE_HPP__
#define ZOPER_BOARDSCENENODE_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>

namespace zoper
{
    using namespace lib;

	class BoardSceneNode : public scene::SceneNode
	{
	private:
		using BaseClass = scene::SceneNode;
	public:
		BoardSceneNode(scene::SceneNode* parent, str name, const Rectf32 &tileBox);
		virtual ~BoardSceneNode();

		void setTileColor(scene::Color color);

	private:
		sptr<scene::nodes::NodeQuad> m_backgroundTile;
		sptr<scene::nodes::NodeShape> m_pointInCenter;
	};
}

#endif