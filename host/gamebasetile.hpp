#ifndef ZOPER_GAMEBASETILE_HPP__
#define ZOPER_GAMEBASETILE_HPP__

#pragma once

#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
#include <lib/board/itilescontroller.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile
	{
	public:
		explicit GameBaseTile(const lib::draw::SceneNodeSPtr &parent, lib::str_const name, lib::board::BoardTileData data, const lib::Rectf32 &box, const lib::u32 pointCount = 30);
		virtual ~GameBaseTile() = default;

		lib::ForwardProperty<lib::vector2df> position;

		const lib::str_const &name() const noexcept { return m_sceneNode->name(); }

		lib::draw::Color getColorForToken() const;
		lib::draw::SceneNodeSPtr m_sceneNode;
	protected:
		lib::sptr<lib::draw::nodes::NodeShape> m_node;
	};
}

#endif
