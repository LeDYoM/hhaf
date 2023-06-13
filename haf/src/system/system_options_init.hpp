HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_SYSTEM_OPTIONS_INIT_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_OPTIONS_INIT_INCLUDE_HPP

#include "system/init_system_options.hpp"

namespace haf::scene
{
class SceneManager;
}

namespace haf::sys
{

class SharedDataSystem;
class TimeSystem;
class Window;
class InputSystem;
class ResourceManager;
class RenderSystem;
class RandomSystem;
class FileSystem;
class SimulationSystem;

template <typename T>
bool getInitSystem(InitSystemOptions const&);

template <>
inline bool getInitSystem<SharedDataSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_shared_data_system;
}

template <>
inline bool getInitSystem<scene::SceneManager>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_scene_manager;
}

template <>
inline bool getInitSystem<Window>(InitSystemOptions const& init_system_options)
{
    return init_system_options.init_window_system;
}

template <>
inline bool getInitSystem<InputSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_input_system;
}

template <>
inline bool getInitSystem<ResourceManager>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_resource_manager;
}

template <>
inline bool getInitSystem<RenderSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_render_system;
}

template <>
inline bool getInitSystem<RandomSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_random_system;
}

template <>
inline bool getInitSystem<FileSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_file_system;
}

template <>
inline bool getInitSystem<TimeSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_time_system;
}

template <>
inline bool getInitSystem<SimulationSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_simulation_system;
}

template <typename T>
inline void setInitSystem(InitSystemOptions&);

template <>
inline void setInitSystem<SharedDataSystem>(
    InitSystemOptions& init_system_options)
{
    init_system_options.init_shared_data_system = true;
}

template <>
inline void setInitSystem<TimeSystem>(InitSystemOptions& init_system_options)
{
    init_system_options.init_time_system = true;
}

template <>
inline void setInitSystem<scene::SceneManager>(
    InitSystemOptions& init_system_options)
{
    init_system_options.init_scene_manager = true;
}

template <>
inline void setInitSystem<Window>(InitSystemOptions& init_system_options)
{
    init_system_options.init_window_system = true;
}

template <>
inline void setInitSystem<InputSystem>(InitSystemOptions& init_system_options)
{
    init_system_options.init_input_system = true;
}

template <>
inline void setInitSystem<ResourceManager>(
    InitSystemOptions& init_system_options)
{
    init_system_options.init_resource_manager = true;
}

template <>
inline void setInitSystem<RenderSystem>(InitSystemOptions& init_system_options)
{
    init_system_options.init_render_system = true;
}

template <>
inline void setInitSystem<RandomSystem>(InitSystemOptions& init_system_options)
{
    init_system_options.init_random_system = true;
}

template <>
inline void setInitSystem<FileSystem>(InitSystemOptions& init_system_options)
{
    init_system_options.init_file_system = true;
}

template <>
inline void setInitSystem<SimulationSystem>(
    InitSystemOptions& init_system_options)
{
    init_system_options.init_simulation_system = true;
}

}  // namespace haf::sys

#endif
