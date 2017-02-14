#include "tile.hpp"
#include <lib/draw/nodes/nodeshape.hpp>

namespace zoper
{
	lib::u32 Tile::_tileCounter{ 0 };

	Tile::Tile(const lib::draw::SceneNodeSPtr &parent, lib::str_const name, lib::board::BoardTileData data, const lib::Rectf32 &box) :
		GameBaseTile{ parent, name + std::to_string(_tileCounter) + std::to_string(_tileCounter), data, box }
	{
		++_tileCounter;
		m_sceneNode->setColor(getColorForToken());
	}

	Tile::~Tile() = default;

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}

	void Tile::remove()
	{
		m_sceneNode->parent()->removeSceneNode(m_sceneNode);
		m_sceneNode.reset();
	}
}
