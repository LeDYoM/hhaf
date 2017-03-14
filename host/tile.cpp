#include "tile.hpp"
#include <lib/draw/nodes/nodeshape.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::draw;
	using namespace lib::board;

	u32 Tile::_tileCounter{ 0 };

	Tile::Tile(lib::draw::SceneNode* const parent, str_const&& name, BoardTileData data, const Rectf32 &box) :
		GameBaseTile{ parent, name + std::to_string(_tileCounter) + std::to_string(_tileCounter), data }
	{
		++_tileCounter;
		m_node = createRenderizable<nodes::NodeShape>("Node", 30);
		m_node->box = box;
		m_node->configure();
		setColor(getColorForToken());
	}

	Tile::~Tile() = default;

	void Tile::resetTileCounter()
	{
		_tileCounter = 0;
	}
}