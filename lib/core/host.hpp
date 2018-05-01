#pragma once

#ifndef LIB_HOST_MAIN_INCLUDE_HPP__
#define LIB_HOST_MAIN_INCLUDE_HPP__

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
        class SceneManager;
    }
    namespace core
    {
        class Window;
        class ResourceManager;
        class Randomizer;
        class DebugSystem;
        class HostPrivate;

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

            void exitProgram();

            inline Window const &parentWindow() const noexcept { return *m_window; }
            inline Window &parentWindow() noexcept { return *m_window; }
            inline ResourceManager const &resourceManager() const  noexcept { return *m_resourceManager; }
            inline ResourceManager &resourceManager()  noexcept { return *m_resourceManager; }
            inline input::InputSystem const &inputSystem() const noexcept { return *m_inputSystem; }
            inline input::InputSystem &inputSystem() noexcept { return *m_inputSystem; }
            inline DebugSystem const &debugSystem() const noexcept { return *m_debugSystem; }
            inline DebugSystem &debugSystem() noexcept { return *m_debugSystem; }
            inline scene::SceneManager &sceneManager() noexcept { return *m_sceneManager; }
            inline const scene::SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

            template <typename T>
            T &app() { return *(dynamic_cast<T*>(m_iapp.get())); }

            const str appId() const;

            inline Randomizer &randomizer() const noexcept { return *m_randomizer; }

        private:
            friend class lib::core::HostPrivate;
            uptr<HostPrivate> m_private;

            bool loopStep();

            static Host *m_instance;

            AppState m_state;
            uptr<Window> m_window;
            uptr<IApp> m_iapp;
            uptr<ResourceManager> m_resourceManager;
            uptr<Randomizer> m_randomizer;
            uptr<DebugSystem> m_debugSystem;
            uptr<input::InputSystem> m_inputSystem;
            uptr<scene::SceneManager> m_sceneManager;
            bool exit{ false };
        };
    }

    template <typename AppType>
    inline AppType &app() {
        return core::Host::host().app<AppType>();
    }

    inline core::Host &host() noexcept { return core::Host::host(); }
    inline core::Window &window() noexcept { return core::Host::host().parentWindow(); }
    inline core::ResourceManager &resourceManager() noexcept { return core::Host::host().resourceManager(); }
    inline core::Randomizer &randomizer() noexcept { return core::Host::host().randomizer(); }
    inline core::DebugSystem &debugSystem() noexcept { return core::Host::host().debugSystem(); }
    inline scene::SceneManager &sceneManager() noexcept { return core::Host::host().sceneManager(); }
}

#endif
