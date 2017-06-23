#include "debugsystem.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/components/debugvarscomponent.hpp>
#include "host.hpp"

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

		void DebugSystem::addDebugVars(const sptr<scene::Scene>&scene)
		{
			auto dbc(scene->ensureComponentOfType<scene::DebugVarsComponent>());
		}

		void DebugSystem::setMatrixMultiplicationPerFrame(u32 & var)
		{
			auto dbc(host().currentScene()->ensureComponentOfType<scene::DebugVarsComponent>());
			dbc->addOrUpdateDebugVar("Matrix mul per Frame:", str(var) );
		}

		void DebugSystem::showVarsNextFrame()
		{
			auto dbc(host().currentScene()->ensureComponentOfType<scene::DebugVarsComponent>());
			dbc->showVarsNextFrame();
		}

	}
}
