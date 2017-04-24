#include "debugsystem.hpp"
#include "log.hpp"
#include <lib/draw/scenenode.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/components/debugvarscomponent.hpp>

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
//			dbc->addOrUpdateDebugVar(nullptr,"", "");
		}

		void DebugSystem::setMatrixMultiplicationPerFrame(u32 & var)
		{

		}

	}
}
