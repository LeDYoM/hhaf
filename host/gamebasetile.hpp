#ifndef ZOPER_GAMEBASETILE_HPP__
#define ZOPER_GAMEBASETILE_HPP__

#pragma once

#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
#include <lib/board/itilescontroller.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile, public lib::draw::SceneNode
	{
	public:
		explicit GameBaseTile(lib::draw::SceneNode* const parent, lib::str name, lib::board::BoardTileData data);
		virtual ~GameBaseTile() = default;

		lib::draw::Color getColorForToken() const;

	protected:
		lib::sptr<lib::draw::nodes::NodeShape> m_node;
	};
}

#endif