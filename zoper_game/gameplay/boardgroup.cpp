#include "boardgroup.hpp"
#include "tile.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>

#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>

using namespace lib::scene;
using namespace lib::scene::nodes;

namespace zoper
{
	BoardGroup::BoardGroup(SceneNode* parent, str name, vector2dst size) :
		BaseClass{ parent, std::move(name), size } {}

    BoardGroup::~BoardGroup() {}

    void BoardGroup::onCreated()
    {
        BaseClass::onCreated();

        m_mainBoardrg = parent()->createSceneNode("mainBoard");

        Rectf32 textBox{ scenePerspective() };
        position = textBox.leftTop();
        sceneNodeSize = textBox.size();

        const Rectf32 bBox(scenePerspective());

        Rectf32 tileBox({}, cellSize());
        for (size_type y{ 0U }; y < tableSize().y; ++y) {
            for (size_type x{ 0U }; x < tableSize().x; ++x) {
                static_cast<void>(createNodeAt({ x,y }, make_str("BoardGroupTile_", x, y), tileBox));
            }
        }

        p_boardModel = ensureComponentOfType<board::BoardModelComponent>();
        p_boardModel->initialize(tableSize(), this);
	}

	void BoardGroup::tileRemoved(const vector2dst, board::SITilePointer tile)
	{
		assert_release(std::dynamic_pointer_cast<Tile>(tile) != nullptr, "Trying to delete invalid type from board");
		m_mainBoardrg->removeSceneNode(std::dynamic_pointer_cast<Tile>(tile));
	}
}