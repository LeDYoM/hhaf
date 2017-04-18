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

		void DebugSystem::update()
		{
		}

		void DebugSystem::addDebugVars(const sptr<draw::Scene>& scene)
		{
			scene->createSceneNode<gui::TextGroup>("DebugVars_"+scene->name());
		}

		void DebugSystem::addStandardDebugVars()
		{
			m_currentDebugVarsNode->addTextLine("Test: 0");
		}

		void DebugSystem::activeSceneChanged(const sptr<draw::Scene>& currentScene)
		{
			if (m_currentDebugVarsNode && m_currentDebugVarsNode->parentScene()->isActiveScene()) {
				return;
			}

		}

		sptr<gui::TextGroup> DebugSystem::debugVarsNodeForScene(const sptr<draw::Scene>& currentScene)
		{
			return sptr<gui::TextGroup>();
		}
	}
}
