#pragma once

#ifndef ZOPER_BOARDSCENENODE_INCLUDE_HPP__
#define ZOPER_BOARDSCENENODE_INCLUDE_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/color.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/scenenodetypes.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;

	class BoardSceneNode : public SceneNode
	{
	private:
		using BaseClass = SceneNode;
	public:
		BoardSceneNode(SceneNode* parent, str name, const Rectf32 &tileBox);
		virtual ~BoardSceneNode();

		void setTileColor(Color color);

	private:
		sptr<nodes::NodeQuad> m_backgroundTile;
		sptr<ShapeSceneNode> m_pointInCenter;
	};
}

#endif