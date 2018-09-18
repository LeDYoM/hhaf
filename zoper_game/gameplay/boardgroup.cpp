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
        p_boardModel->initialize(tableSize(), nullptr);

        /*
        * Delete someday.
        p_boardModel->TileAdded.connect([this](const vector2dst position_, board::SITilePointer tile)
        {
            // Tile appeared
//            tile->tileAdded(position_);
        });

        */
        p_boardModel->TileRemoved.connect([this](const vector2dst position_, board::SITilePointer tile)
        {
            assert_release(std::dynamic_pointer_cast<Tile>(tile) != nullptr, "Trying to delete invalid type from board");
//            tile->tileRemoved(position_);
            m_mainBoardrg->removeSceneNode(std::dynamic_pointer_cast<Tile>(tile));
        });

        /*
        * Delete someday.
        p_boardModel->TileChanged.connect([this](const vector2dst position_, board::SITilePointer tile,
            const board::BoardTileData oldValue, const board::BoardTileData newValue)
        {
//            tile->tileChanged(position_, oldValue, newValue);
        });

        p_boardModel->TileMoved.connect([this](const vector2dst source, const vector2dst dest, board::SITilePointer tile)
        {
//            tile->tileMoved(source, dest);
        });
        */
	}

}