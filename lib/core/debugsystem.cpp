#include "debugsystem.hpp"
#include "log.hpp"
#include <lib/draw/scenenode.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/components/debugvarscomponent.hpp>
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

		void DebugSystem::addDebugVars(const sptr<draw::Scene>&scene)
		{
			auto dbc(scene->ensureComponentOfType<draw::DebugVarsComponent>());
		}

		void DebugSystem::setMatrixMultiplicationPerFrame(u32 & var)
		{
			auto dbc(host().currentScene()->ensureComponentOfType<draw::DebugVarsComponent>());
			dbc->addOrUpdateDebugVar("Matrix mul per Frame:",std::to_string(var));
		}

		void DebugSystem::showVarsNextFrame()
		{
			auto dbc(host().currentScene()->ensureComponentOfType<draw::DebugVarsComponent>());
			dbc->showVarsNextFrame();
		}

	}
}
