#include "debugsystem.hpp"
#include <lib/include/core/log.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/components/debugvarscomponent.hpp>
#include "host.hpp"

namespace lib::core
{
    DebugSystem::DebugSystem(Host& host)
        : AppService{ host } {}

    DebugSystem::~DebugSystem() = default;

	void DebugSystem::addDebugVars(const sptr<scene::Scene>&scene)
	{
		auto dbc(scene->ensureComponentOfType<scene::DebugVarsComponent>());
	}

	void DebugSystem::setMatrixMultiplicationPerFrame(u32 &)
	{
//			auto dbc(host().currentScene()->ensureComponentOfType<scene::DebugVarsComponent>());
//			dbc->addOrUpdateDebugVar("Matrix mul per Frame:", str(var) );
	}

	void DebugSystem::showVarsNextFrame()
	{
//			auto dbc(host().currentScene()->ensureComponentOfType<scene::DebugVarsComponent>());
//			dbc->showVarsNextFrame();
	}
}
