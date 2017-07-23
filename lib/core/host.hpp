#ifndef __LIB_APPCONTROLLER_HPP__
#define __LIB_APPCONTROLLER_HPP__

#pragma once

#include <mtypes/include/types.hpp>
#include <lib/include/iapp.hpp>

namespace lib
{
	namespace input
	{
		class InputSystem;
	}
	namespace scene
	{
		class RenderStatesStack;
		class SceneManager;
	}
	namespace core
	{
		class Window;
		class ResourceManager;
		class EventManager;
		class Randomizer;
		class DebugSystem;
		class PropertiesFileManager;

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

			void addScene(sptr<scene::Scene> newScene);
			void setScene(const str &name);

			void addScenes(vector<sptr<scene::Scene>> &&sceneVector);
			sptr<scene::Scene> getSceneByName(const str &name) const;

			void exitProgram();

			void setScene(sptr<scene::Scene> &&scene);

			inline Window const &parentWindow() const noexcept { return *m_window; }
			inline Window &parentWindow() noexcept { return *m_window; }
			inline ResourceManager const &resourceManager() const  noexcept { return *m_resourceManager; }
			inline ResourceManager &resourceManager()  noexcept { return *m_resourceManager; }
			inline EventManager const &eventManager() const  noexcept { return *m_eventManager; }
			inline EventManager &eventManager()  noexcept { return *m_eventManager; }
			inline input::InputSystem const &inputSystem() const noexcept { return *m_inputSystem; }
			inline input::InputSystem &inputSystem() noexcept { return *m_inputSystem; }
			inline DebugSystem const &debugSystem() const noexcept { return *m_debugSystem; }
			inline DebugSystem &debugSystem() noexcept { return *m_debugSystem; }
			inline PropertiesFileManager &propertiesFileManager() noexcept { return *m_propertiesFileManager; }
			inline const PropertiesFileManager &propertiesFileManager() const noexcept { return *m_propertiesFileManager; }
			inline scene::SceneManager &sceneManager() noexcept { return *m_sceneManager; }
			inline const scene::SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

			const str appId() const;

			inline const scene::RenderStatesStack &rStates() const noexcept { return *m_renderStates; }
			inline scene::RenderStatesStack &rStates() noexcept { return *m_renderStates; }

			inline Randomizer &randomizer() const noexcept { return *m_randomizer; }
			inline const sptr<scene::Scene> &currentScene() const noexcept { return m_currentScene; }

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
			uptr<DebugSystem> m_debugSystem{ nullptr };
			uptr<input::InputSystem> m_inputSystem{ nullptr };
			uptr<PropertiesFileManager> m_propertiesFileManager{ nullptr };
			uptr<scene::SceneManager> m_sceneManager{ nullptr };
			bool exit{ false };
			vector<sptr<scene::Scene>> m_scenes;
			sptr<scene::Scene> m_currentScene{ nullptr };
			sptr<scene::Scene> m_nextScene{ nullptr };
			vector<str> m_params;
			uptr<scene::RenderStatesStack> m_renderStates;
		};
	}

	inline core::Host &host() noexcept { return core::Host::host(); }
	inline core::Window &window() noexcept { return core::Host::host().parentWindow(); }
	inline core::ResourceManager &resourceManager() noexcept { return core::Host::host().resourceManager(); }
	inline core::Randomizer &randomizer() noexcept { return core::Host::host().randomizer(); }
	inline core::DebugSystem &debugSystem() noexcept { return core::Host::host().debugSystem(); }
	inline core::PropertiesFileManager &propertiesFileManager() noexcept { return core::Host::host().propertiesFileManager(); }

}

#endif
