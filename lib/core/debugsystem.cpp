#include "debugsystem.hpp"
#include "log.hpp"
#include <lib/gui/textgroup.hpp>
#include <lib/draw/scenenode.hpp>

namespace lib
{
	namespace core
	{
		DebugSystem::DebugSystem()
		{
			logConstruct_NOPARAMS;

//			m_debugVarsNode = 
		}

		DebugSystem::~DebugSystem()
		{
			logDestruct_NOPARAMS;
		}

		void DebugSystem::update()
		{
			if (m_debugVarsNode) {
				m_debugVarsNode->draw();
			}
		}
	}
}
