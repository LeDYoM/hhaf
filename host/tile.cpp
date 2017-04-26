#include "tile.hpp"
#include <lib/draw/nodes/nodeshape.hpp>

#include <string>

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;
	using namespace lib::board;

	u32 Tile::m_tileCounter{ 0 };

	Tile::Tile(lib::draw::SceneNode* const parent, str name, BoardTileData data, const Rectf32 &box) :
		GameBaseTile{ parent, name + std::to_string(m_tileCounter) + std::to_string(m_tileCounter), data }
	{
		++m_tileCounter;
		m_node = createRenderizable<nodes::NodeShape>("Node", 30);
		m_node->box = box;
		m_node->configure();
		setColor(getColorForToken());
	}

	Tile::~Tile() = default;

	void Tile::resetTileCounter()
	{
		m_tileCounter = 0;
	}
}