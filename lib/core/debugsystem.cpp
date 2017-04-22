#include "debugsystem.hpp"
#include "log.hpp"
#include <lib/gui/textgroup.hpp>
#include <lib/draw/scenenode.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	namespace core
	{
		DebugSystem::DebugSystem()
		{
			logConstruct_NOPARAMS;
		}

		DebugSystem::~DebugSystem()
		{
			logDestruct_NOPARAMS;
		}

		void DebugSystem::addDebugVars(const sptr<draw::Scene>&scene)
		{
			auto dbc(scene->ensureComponentOfType<DebugVarsComponent>());
			dbc->addOrUpdateDebugVar("", "");
		}

	}
}
