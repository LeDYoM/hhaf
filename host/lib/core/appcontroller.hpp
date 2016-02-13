#ifndef __LIB_APPCONTROLLER_HPP__
#define __LIB_APPCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include <lib/core/vecsptr.hpp>
#include <vector>
#include <string>

namespace lib
{
	namespace scn
	{
		class SceneManager;
		class Scene;
	}
	namespace core
	{
		class Window;
		class ResourceManager;
		class EventManager;
	
		class AppController
		{
		public:
			enum class AppState
			{
				NotInitialized,
				ReadyToStart,
				Executing,
				ReadyToTerminate,
				Terminated
			};
			AppController(uptr<IApp> iapp);
			virtual ~AppController();
			
			bool update();
			uptr<Window> const &parentWindow() const { return m_window; }
			uptr<ResourceManager> const &resourceManager() const { return m_resourceManager; }
			uptr<EventManager> const &eventManager() const { return m_eventManager; }

			const std::string appId() const;

		protected:
			bool loopStep();
		private:
			AppState m_state;
			uptr<Window> m_window{ nullptr };
			uptr<IApp> m_iapp{ nullptr };
			uptr<scn::SceneManager> m_sceneManager{ nullptr };
			uptr<ResourceManager> m_resourceManager{ nullptr };
			uptr<EventManager> m_eventManager{ nullptr };

		};
	}
}

#endif
