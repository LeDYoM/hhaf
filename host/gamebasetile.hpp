#ifndef ZOPER_GAMEBASETILE_HPP__
#define ZOPER_GAMEBASETILE_HPP__

#pragma once

#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/board/itilescontroller.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile, public lib::scene::SceneNode
	{
	public:
		explicit GameBaseTile(lib::scene::SceneNode* const parent, lib::str name, lib::board::BoardTileData data);
		virtual ~GameBaseTile() = default;

		lib::scene::Color getColorForToken() const;

	protected:
		lib::sptr<lib::scene::nodes::NodeShape> m_node;
	};
}

#endif