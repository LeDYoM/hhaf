#ifndef __LIB_APPCONTROLLER_HPP__
#define __LIB_APPCONTROLLER_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/include/iapp.hpp>

#include <vector>
#include <string>

namespace lib
{
	namespace draw
	{
		class RenderStates;
	}
	namespace core
	{
		class Window;
		class ResourceManager;
		class EventManager;
		class Randomizer;

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

			void addScene(sptr<draw::Scene> newScene);
			void setScene(const std::string &name);

			void addScenes(std::vector<sptr<draw::Scene>> &&sceneVector);
			sptr<draw::Scene> getSceneByName(const std::string &name) const;

			void exitProgram();

			void setScene(sptr<draw::Scene> &&scene);

			inline Window const &parentWindow() const noexcept { return *m_window; }
			inline Window &parentWindow()  noexcept { return *m_window; }
			inline ResourceManager const &resourceManager() const  noexcept { return *m_resourceManager; }
			inline ResourceManager &resourceManager()  noexcept { return *m_resourceManager; }
			inline EventManager const &eventManager() const  noexcept { return *m_eventManager; }
			inline EventManager &eventManager()  noexcept { return *m_eventManager; }

			const std::string appId() const;

			inline draw::RenderStates &rStates() const noexcept { return *m_renderStates; }
			inline draw::RenderStates &rStates() noexcept { return *m_renderStates; }

			inline const Randomizer &randomizer() const noexcept { return *m_randomizer; }

		private:
			bool loopStep();
			void updateScene();

			static Host *m_instance;
			AppState m_state;
			uptr<Window> m_window{ nullptr };
			uptr<IApp> m_iapp{ nullptr };
			uptr<ResourceManager> m_resourceManager{ nullptr };
			uptr<EventManager> m_eventManager{ nullptr };
			uptr<Randomizer> m_randomizer;
			bool exit{ false };
			std::vector<sptr<draw::Scene>> m_scenes;
			sptr<draw::Scene> m_currentScene{ nullptr };
			sptr<draw::Scene> m_nextScene{ nullptr };
			std::vector<std::string> m_params;
			uptr<draw::RenderStates> m_renderStates;
		};
	}

	inline core::Host &host() noexcept { return core::Host::host(); }
}

#endif
