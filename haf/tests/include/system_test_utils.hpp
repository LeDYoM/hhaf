HTPS_PRAGMA_ONCE
#ifndef HAF_SYSTEM_TESTS_UTILS_INCLUDE_HPP
#define HAF_SYSTEM_TESTS_UTILS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "system/system_provider.hpp"
#include <haf/include/system/subsystem_view.hpp>
#include "shareddata/shared_data_system.hpp"
#include "time/time_system.hpp"
#include "scene/scene_manager.hpp"
#include "system/system_options_init.hpp"

template <typename T>
class TestSystem
{
public:
    TestSystem() : system_provider_{}, init_system_options_{} {}

    haf::sys::SubSystemViewer getSubSystemViewer()
    {
        return haf::sys::SubSystemViewer{&systemProvider()};
    }

    void init()
    {
        setInitSystemOptions(init_system_options_);
        system_provider_.createSystems(init_system_options_);
    }

    virtual ~TestSystem() = default;

    void setInitSystemOptions(haf::sys::InitSystemOptions& init_system_options)
    {
        haf::sys::setInitSystem<T>(init_system_options);
    }

    haf::sys::SystemProvider& systemProvider() noexcept
    {
        return system_provider_;
    }

    haf::sys::SystemProvider const& systemProvider() const noexcept
    {
        return system_provider_;
    }

    template <typename S>
    S& system()
    {
        return system_provider_.system<S>();
    }

    template <typename S>
    S const& system() const
    {
        return system_provider_.system<S>();
    }

private:
    haf::sys::SystemProvider system_provider_;
    haf::sys::InitSystemOptions init_system_options_;
};

using TestSharedDataSystem = TestSystem<haf::sys::SharedDataSystem>;
using TestTimeSystem       = TestSystem<haf::sys::TimeSystem>;
using TestSceneManager     = TestSystem<haf::scene::SceneManager>;

template <typename T>
htps::uptr<T> makeTestSystem()
{
    auto t = htps::muptr<T>();
    t->init();
    return t;
}

#endif
