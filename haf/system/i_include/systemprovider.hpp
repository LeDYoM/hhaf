#pragma once

#ifndef HAF_SYSTEM_PROVIDER_INCLUDE_HPP
#define HAF_SYSTEM_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/system/include/isystemprovider.hpp>
#include <haf/system/include/icontrollablesystemprovider.hpp>

namespace haf
{
class IApp;
}

namespace haf::backend
{
class BackendFactory;
}

namespace haf::scene
{
class SceneManager;
}

namespace haf::sys
{
class InputSystem;
class Window;
class ResourceManager;
class RandomSystem;
class FileSystem;
class SimulationSystem;
class TimeSystem;
class RenderSystem;
class SharedDataSystem;
} // namespace haf::sys

namespace haf::sys
{
class SystemProvider final
    : public ISystemProvider,
      public IControllableSystemProvider
{
public:
    SystemProvider();
    ~SystemProvider();

    void init(IApp *iapp) override;
    bool runStep() override;
    void terminate() override;

    template <typename T>
    T &app() { return *(dynamic_cast<T *>(&app())); }

    template <typename T>
    const T &app() const { return *(dynamic_cast<T *>(&app())); }

    IApp &app();
    const IApp &app() const;

    const Window &parentWindow() const noexcept;
    Window &parentWindow() noexcept;
    const ResourceManager &resourceManager() const noexcept;
    ResourceManager &resourceManager() noexcept;
    const sys::InputSystem &inputSystem() const noexcept;
    sys::InputSystem &inputSystem() noexcept;
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
    SharedDataSystem &sharedDataSystem() noexcept;
    const SharedDataSystem &sharedDataSystem() const noexcept;

private:
    struct SystemProviderPrivate;
    mtps::uptr<SystemProviderPrivate> p_;
};
} // namespace haf::sys

#endif
