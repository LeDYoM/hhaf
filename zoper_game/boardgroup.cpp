#include "boardgroup.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>

using namespace lib::scene;
using namespace lib::scene::nodes;

namespace zoper
{
	BoardGroup::BoardGroup(SceneNode* parent, str name, sptr<GameData> gameData) :
		BaseClass{ parent, std::move(name) }, m_gameData{ std::move(gameData) } {}

	BoardGroup::~BoardGroup() = default;

	void BoardGroup::onCreated()
	{
		BaseClass::onCreated();

		Rectf32 textBox{ scenePerspective() };
		position = textBox.leftTop();
		sceneNodeSize = textBox.size();

		const Rectf32 bBox(scenePerspective());

		f32 currentx{};
		f32 currenty{};
		for (u32 y{ 0 }; y < m_gameData->size.y; ++y) {
			for (u32 x{ 0 }; x < m_gameData->size.x; ++x) {
				auto tileParentNode (createNodeAt({ x,y }, make_str("BoardGroupTile_", x, y)));

				auto tileBackground(tileParentNode->createRenderizable<NodeQuad>("backgroundTile"));
//				tileBackground->box = tileBox;

				// Size of the point in the middle of the tile
				constexpr vector2df centerPointSize{ 15,15 };

				auto node(tileParentNode->createRenderizable<NodeShape>("backgroundTilePoint_", 30));
//				node->box = { tileBox.center() - (centerPointSize / 2), centerPointSize };
				node->color = colors::White;

//				currentx += tileSize().x;
			}
			currentx = 0;
//			currenty += tileSize().y;
//			m_backgroundTiles.push_back(std::move(column));
		}

	}

}