#ifndef __GAMEBASETILE_HPP__
#define __GAMEBASETILE_HPP__

#include <lib/board/itilescontroller.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodes/nodeshape.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile
	{
	public:
		explicit GameBaseTile(const lib::draw::SceneNodeSPtr &parent, lib::str_const name, lib::board::BoardTileData data, const lib::Rectf32 &box, const lib::u32 pointCount = 30);
		virtual ~GameBaseTile() = default;

		lib::ForwardProperty<lib::vector2df> position;

		lib::str_const name() const { return m_sceneNode->name(); }

		lib::draw::Color getColorForToken() const;
		lib::draw::SceneNodeSPtr m_sceneNode;
		lib::sptr<lib::draw::nodes::NodeShape> m_node;
	};
}

#endif
