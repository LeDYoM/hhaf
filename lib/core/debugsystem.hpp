#ifndef LIB_DEBUGSYSTEM_INCLUDE_HPP
#define LIB_DEBUGSYSTEM_INCLUDE_HPP

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>

namespace lib
{
	namespace gui
	{
		class TextGroup;
	}
	namespace draw
	{
		class Scene;
	}
	namespace core
	{
		class DebugSystem final : public AppService
		{
		public:
			DebugSystem();
			~DebugSystem();

			void update();
			void addDebugVars(const sptr<draw::Scene> &scene);
			void addStandardDebugVars();
		private:
			void activeSceneChanged(const sptr<draw::Scene> &currentScene);
			sptr<gui::TextGroup> debugVarsNodeForScene(const sptr<draw::Scene> &currentScene);
			sptr<gui::TextGroup> m_currentDebugVarsNode;
		};
	}
}

#endif
