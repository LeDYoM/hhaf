#pragma once

#ifndef LIB_SYSTEM_PROVIDER_INCLUDE_HPP
#define LIB_SYSTEM_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib
{
    class IApp;
}

namespace lib::backend
{
    class BackendFactory;
}

namespace lib::input
{
    class InputSystem;
}

namespace lib::scene
{
    class SceneManager;
}

namespace lib::core
{
    class Window;
    class ResourceManager;
    class RandomSystem;
    class FileSystem;
    class SimulationSystem;
    class TimeSystem;
    class RenderSystem;
}

namespace lib::core
{
    class SystemProvider final
    {
    public:
        SystemProvider();
        ~SystemProvider();
        
        void init(IApp *iapp);
        void terminate();

        template <typename T>
        T &app() { return *(dynamic_cast<T*>(&app())); }

        template <typename T>
        const T &app() const { return *(dynamic_cast<T*>(&app())); }

        IApp &app();
        const IApp &app() const;

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
        const TimeSystem &timeSystem() const noexcept;
        TimeSystem &timeSystem() noexcept;
        const backend::BackendFactory &backendFactory() const noexcept;
        backend::BackendFactory &backendFactory() noexcept;
        const RenderSystem &renderSystem() const noexcept;
        RenderSystem &renderSystem() noexcept;

        bool runStep();

    private:
        struct SystemProviderPrivate;
        uptr<SystemProviderPrivate> p_;
    };
}

#endif
