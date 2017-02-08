#ifndef __GAMEBASETILE_HPP__
#define __GAMEBASETILE_HPP__

#include <lib/board/itilescontroller.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/draw/nodeshape.hpp>

namespace zoper
{
	class GameBaseTile : public lib::board::ITile, public lib::draw::SceneNode
	{
	public:
		explicit GameBaseTile(lib::board::BoardTileData data, const lib::Rectf32 &box, const std::string &baseName, const lib::u32 pointCount = 30);
		virtual ~GameBaseTile() = default;

		lib::draw::Color getColorForToken() const;
		lib::sptr<lib::draw::NodeShape> m_node;
	};
}

#endif
