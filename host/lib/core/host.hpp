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
			enum class AppState : u8;
			Host(int argc, char *argv[]);
			~Host();

			bool setApplication(uptr<IApp> iapp);
			int run();
			bool update();

			void addScene(sptr<scn::Scene> newScene);
			void setScene(const std::string &name);

			void addScenes(const std::vector<sptr<scn::Scene>> &&sceneVector);
			sptr<scn::Scene> getSceneByName(const std::string &name) const;

			void exitProgram();

			void setScene(sptr<scn::Scene> scene);

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

			void updateActiveSceneStates(const sptr<scn::Scene> &, const sptr<scn::Scene> &) const noexcept;

			static Host *m_instance;
			AppState m_state;
			uptr<Window> m_window{ nullptr };
			uptr<IApp> m_iapp{ nullptr };
			uptr<ResourceManager> m_resourceManager{ nullptr };
			uptr<EventManager> m_eventManager{ nullptr };
			bool exit{ false };
			std::vector<sptr<scn::Scene>> m_scenes;
			sptr<scn::Scene> m_currentScene{ nullptr };
			std::vector<std::string> m_params;
		};
	}

	inline core::Host &host() noexcept { return core::Host::host(); }
}

#endif
