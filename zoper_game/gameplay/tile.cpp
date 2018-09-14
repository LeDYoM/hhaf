#include "tile.hpp"
#include <lib/scene/renderizables/nodeshape.hpp>

#include <lib/include/core/log.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::board;

	u32 Tile::m_tileCounter{ 0 };

	Tile::Tile(SceneNode* const parent, str name, BoardTileData data, const Rectf32 &box) :
		GameBaseTile{ parent, name + str(m_tileCounter) + str(m_tileCounter), data }
	{
		++m_tileCounter;
		m_node = createRenderizable<nodes::NodeShape>("Node", 30);
		m_node->box = box;
		m_node->color = getColorForToken();
	}

	Tile::~Tile() = default;

	void Tile::resetTileCounter()
	{
		m_tileCounter = 0;
	}

    void Tile::tileAdded(const vector2dst & position_)
    {
        log_debug_info("Token ", name(), " appeared at ", position_);
        // Set the position in the scene depending on the board position
//        setBoardPosition(position);
    }
}