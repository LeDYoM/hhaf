HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_SYSTEM_PROVIDER_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_PROVIDER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/system/isystem_provider.hpp>

namespace haf
{
class IApp;

namespace backend
{
class BackendFactory;
}

namespace scene
{
class SceneManager;
}

namespace sys
{
class InputSystem;
class WindowSystem;
class ResourceManager;
class RandomSystem;
class FileSystem;
class SimulationSystem;
class TimeSystem;
class RenderSystem;
class SharedDataSystem;
class DebugSystem;
}  // namespace sys
}  // namespace haf

namespace haf::sys
{
struct InitSystemOptions;

class SystemProvider : public ISystemProvider
{
public:
    SystemProvider();
    ~SystemProvider() override;

    SystemProvider(SystemProvider const&) = delete;
    SystemProvider& operator=(SystemProvider const&) = delete;
    SystemProvider(SystemProvider&&) = default;
    SystemProvider& operator=(SystemProvider&&) = default;

    void setBackend(htps::rptr<backend::BackendFactory> backend_factory);
    void createSystems(InitSystemOptions const& init_system_options);
    void init(htps::rptr<IApp> iapp,
              htps::rptr<backend::BackendFactory> backend_factory,
              int const argc,
              char const* const argv[]);
    void terminate();

    backend::BackendFactory const& backendFactory() const noexcept;
    backend::BackendFactory& backendFactory() noexcept;

    IApp& app();
    IApp const& app() const;

    template <typename T>
    T const& system() const noexcept;

    template <typename T>
    T& system() noexcept;

private:
    void instanciateSystems(InitSystemOptions const& init_system_options);
    void initializeSystems(InitSystemOptions const& init_system_options);

    WindowSystem const& windowSystem() const noexcept;
    WindowSystem& windowSystem() noexcept;
    ResourceManager const& resourceManager() const noexcept;
    ResourceManager& resourceManager() noexcept;
    InputSystem const& inputSystem() const noexcept;
    InputSystem& inputSystem() noexcept;
    RandomSystem const& randomSystem() const noexcept;
    RandomSystem& randomSystem() noexcept;
    scene::SceneManager const& sceneManager() const noexcept;
    scene::SceneManager& sceneManager() noexcept;
    FileSystem const& fileSystem() const noexcept;
    FileSystem& fileSystem() noexcept;
    SimulationSystem const& simulationSystem() const noexcept;
    SimulationSystem& simulationSystem() noexcept;
    TimeSystem const& timeSystem() const noexcept;
    TimeSystem& timeSystem() noexcept;
    RenderSystem const& renderSystem() const noexcept;
    RenderSystem& renderSystem() noexcept;
    SharedDataSystem const& sharedDataSystem() const noexcept;
    SharedDataSystem& sharedDataSystem() noexcept;
    DebugSystem const& debugSystem() const noexcept;
    DebugSystem& debugSystem() noexcept;

    struct SystemProviderPrivate;
    htps::PImplPointer<SystemProviderPrivate> p_;
};
}  // namespace haf::sys

#endif
