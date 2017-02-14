#include "gamebasetile.hpp"
#include <lib/core/log.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::board;
	using namespace lib::draw;
	using namespace lib::draw::nodes;

	GameBaseTile::GameBaseTile(const SceneNodeSPtr &parent, str_const name, BoardTileData data, const Rectf32 &box, const u32 pointCount)
		: ITile{ data }
	{
		m_sceneNode = parent->createSceneNode(name);
		position.setForwardProperty(&(m_sceneNode->position));
		m_node = m_sceneNode->createRenderizable<NodeShape>("Node", box, nullptr, pointCount, colors::White);
		setCallback([this]() {m_sceneNode->setColor(getColorForToken()); });
	}

	Color GameBaseTile::getColorForToken() const
	{
		switch (get())
		{
		case 0:
			return colors::Red;
			break;
		case 1:
			return colors::Green;
			break;
		case 2:
			return colors::Blue;
			break;
		case 3:
			return colors::Yellow;
			break;
		case 4:
			return colors::Magenta;
			break;
		default:
			logError("Error value for token: ", get(), " is not supported");
			return colors::White;
			break;
		}
	}

}
