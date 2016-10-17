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
	
		class Host final
		{
		public:
			static bool createHost(int argc, char *argv[]);
			static bool destroyHost() noexcept;

			inline static Host &host() noexcept { return *m_instance; }
			enum class AppState
			{
				NotInitialized,
				ReadyToStart,
				Executing,
				ReadyToTerminate,
				Terminated
			};
			Host(int argc, char *argv[]);
			~Host();

			bool setApplication(uptr<IApp> iapp);
			int run();
			bool update();

			inline Window const &parentWindow() const noexcept { return *m_window; }
			inline Window &parentWindow()  noexcept { return *m_window; }
			inline ResourceManager const &resourceManager() const  noexcept { return *m_resourceManager; }
			inline ResourceManager &resourceManager()  noexcept { return *m_resourceManager; }
			inline EventManager const &eventManager() const  noexcept { return *m_eventManager; }
			inline EventManager &eventManager()  noexcept { return *m_eventManager; }

			const std::string appId() const;
		protected:
			bool loopStep();
		private:
			static Host *m_instance;
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

	inline core::Host &host() noexcept { return core::Host::host(); }
}

#endif
