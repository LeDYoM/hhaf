#pragma once

#ifndef LIB_SYSTEM_PROVIDER_INCLUDE_HPP
#define LIB_SYSTEM_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib
{
    struct WindowCreationParams;
    class IApp;

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
		class FileSystem;
        class SimulationSystem;

        class SystemProvider
        {
        public:
            void init(Host& host, IApp *iapp);
            void terminate();

//            const core::Host &host() const noexcept;
//            core::Host &host() noexcept;

            template <typename T>
            T &app() { return *(dynamic_cast<T*>(&app())); }
            IApp &app();

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
			const FileSystem &fileSystem() const noexcept;
			FileSystem &fileSystem() noexcept;
			const SimulationSystem &simulationSystem() const noexcept;
            SimulationSystem &simulationSystem() noexcept;

        private:
            core::Host* host_;
            IApp* app_;
            uptr<Window> window_;
            uptr<ResourceManager> resource_manager_;
            uptr<input::InputSystem> input_system_;
            uptr<scene::SceneManager> scene_manager_;
            uptr<RandomSystem> random_system_;
			uptr<FileSystem> file_system_;
            uptr<SimulationSystem> simulation_system_;
        };
    }
}

#endif
