#ifndef HAF_SYSTEM_PROVIDER_INCLUDE_HPP
#define HAF_SYSTEM_PROVIDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/system/isystemprovider.hpp>

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
class Window;
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

    void createBackend();
    void setBackend(htps::rptr<backend::BackendFactory> backend_factory);
    void fastInit(InitSystemOptions const& init_system_options);
    void init(htps::rptr<IApp> iapp,
              htps::rptr<backend::BackendFactory> backend_factory,
              int const argc,
              char const* const argv[]);
    void terminate();

    template <typename T>
    T& app()
    {
        return *(dynamic_cast<T*>(&app()));
    }

    template <typename T>
    const T& app() const
    {
        return *(dynamic_cast<T*>(&app()));
    }

    const backend::BackendFactory& backendFactory() const noexcept;
    backend::BackendFactory& backendFactory() noexcept;

    IApp& app();
    const IApp& app() const;

    template <typename T>
    T const& system() const noexcept;

    template <typename T>
    T& system() noexcept;

private:
    const Window& window() const noexcept;
    Window& window() noexcept;
    const ResourceManager& resourceManager() const noexcept;
    ResourceManager& resourceManager() noexcept;
    const sys::InputSystem& inputSystem() const noexcept;
    sys::InputSystem& inputSystem() noexcept;
    const RandomSystem& randomSystem() const noexcept;
    RandomSystem& randomSystem() noexcept;
    const scene::SceneManager& sceneManager() const noexcept;
    scene::SceneManager& sceneManager() noexcept;
    const FileSystem& fileSystem() const noexcept;
    FileSystem& fileSystem() noexcept;
    const SimulationSystem& simulationSystem() const noexcept;
    SimulationSystem& simulationSystem() noexcept;
    const TimeSystem& timeSystem() const noexcept;
    TimeSystem& timeSystem() noexcept;
    const RenderSystem& renderSystem() const noexcept;
    RenderSystem& renderSystem() noexcept;
    const SharedDataSystem& sharedDataSystem() const noexcept;
    SharedDataSystem& sharedDataSystem() noexcept;
    const DebugSystem& debugSystem() const noexcept;
    DebugSystem& debugSystem() noexcept;

    struct SystemProviderPrivate;
    htps::uptr<SystemProviderPrivate> p_;
};
}  // namespace haf::sys

#endif
