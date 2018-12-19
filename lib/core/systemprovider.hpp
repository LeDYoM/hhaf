#pragma once

#ifndef LIB_SYSTEM_PROVIDER_INCLUDE_HPP
#define LIB_SYSTEM_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>


namespace lib
{
    struct WindowCreationParams;

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
        class Host;
        class Window;
        class ResourceManager;
        class RandomSystem;

        class SystemProvider
        {
        public:
            void init(Host& host, const WindowCreationParams& wcp);
            void terminate();
            const Window &parentWindow() const noexcept;
            Window &parentWindow() noexcept;
            const ResourceManager &resourceManager() const  noexcept;
            ResourceManager &resourceManager()  noexcept;
            const input::InputSystem &inputSystem() const noexcept;
            input::InputSystem &inputSystem() noexcept;
            const RandomSystem &randomSystem() const noexcept;
            RandomSystem &randomSystem() noexcept;
            const scene::SceneManager &sceneManager() const noexcept;
            scene::SceneManager &sceneManager() noexcept;


        private:
            uptr<Window> m_window;
            uptr<ResourceManager> m_resourceManager;
            uptr<input::InputSystem> m_inputSystem;
            uptr<scene::SceneManager> m_sceneManager;
            uptr<RandomSystem> random_system_;
        };
    }
}

#endif
