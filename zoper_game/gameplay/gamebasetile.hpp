#pragma once

#ifndef ZOPER_GAMEBASETILE_HPP
#define ZOPER_GAMEBASETILE_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/board/itile.hpp>

namespace zoper
{
    using namespace lib;

	class GameBaseTile : public board::ITile, public scene::SceneNode
	{
	public:
		GameBaseTile(scene::SceneNode* const parent, str name, board::BoardTileData data);
		~GameBaseTile() override = default;

		scene::Color getColorForToken() const;

	protected:
		sptr<scene::nodes::NodeShape> m_node;
	};
}

#endif