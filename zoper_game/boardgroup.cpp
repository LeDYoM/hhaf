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
		BaseClass{ parent, std::move(name), gameData->size }, m_gameData{ std::move(gameData) } {}

	BoardGroup::~BoardGroup() = default;

	void BoardGroup::onCreated()
	{
		BaseClass::onCreated();

		Rectf32 textBox{ scenePerspective() };
		position = textBox.leftTop();
		sceneNodeSize = textBox.size();

		const Rectf32 bBox(scenePerspective());

		Rectf32 tileBox({},cellSize());
		for (size_type y{ 0U }; y < m_gameData->size.y; ++y) {
			for (size_type x{ 0U }; x < m_gameData->size.x; ++x) {
				static_cast<void>(createNodeAt({ x,y }, make_str("BoardGroupTile_", x, y), tileBox));
			}
		}

	}

}