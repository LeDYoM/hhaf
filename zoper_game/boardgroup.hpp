#pragma once

#ifndef ZOPER_BOARDGROUP_HPP__
#define ZOPER_BOARDGROUP_HPP__

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/renderizables/nodequad.hpp>

using namespace lib;

namespace zoper
{
	class BoardGroup : public scene::nodes::TableNode<scene::nodes::NodeQuad>
	{
	private:
		using BaseClass = scene::nodes::TableNode<scene::nodes::NodeQuad>;
	public:
		BoardGroup(scene::SceneNode* parent, str name);
		virtual ~BoardGroup();

		void onCreated() override;
	};
}

#endif
