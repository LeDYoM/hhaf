#include "boardgroup.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/scene/nodes/tablenode.hpp>
#include <lib/scene/renderizables/nodequad.hpp>

using namespace lib::scene;

namespace zoper
{
	BoardGroup::BoardGroup(SceneNode* parent, str name) :
		BaseClass{ parent, std::move(name) }
	{
	}

	BoardGroup::~BoardGroup() = default;

	void BoardGroup::onCreated()
	{
		BaseClass::onCreated();
	}

}