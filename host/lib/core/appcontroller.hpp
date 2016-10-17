#ifndef __LIB_APPCONTROLLER_HPP__
#define __LIB_APPCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>
#include <lib/core/vecsptr.hpp>
#include <lib/include/singleton.hpp>
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
	
		class AppController : public Singleton<AppController>
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
			AppController(int argc, char *argv[]);
			virtual ~AppController();

			bool setApplication(uptr<IApp> iapp);
			int run();
			bool update();

			uptr<Window> const &parentWindow() const { return m_window; }
			uptr<ResourceManager> const &resourceManager() const { return m_resourceManager; }
			uptr<EventManager> const &eventManager() const { return m_eventManager; }

			const std::string appId() const;
		protected:
			bool loopStep();
		private:
			AppState m_state{ AppState::NotInitialized };
			uptr<Window> m_window{ nullptr };
			uptr<IApp> m_iapp{ nullptr };
			uptr<scn::SceneManager> m_sceneManager{ nullptr };
			uptr<ResourceManager> m_resourceManager{ nullptr };
			uptr<EventManager> m_eventManager{ nullptr };
			bool exit{ false };
			std::vector<std::string> m_params;
		};
	}
}

#endif
