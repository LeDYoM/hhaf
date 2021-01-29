#ifndef HAF_SYSTEM_INIT_SYSTEM_OPTIONS_INCLUDE_HPP
#define HAF_SYSTEM_INIT_SYSTEM_OPTIONS_INCLUDE_HPP

namespace haf::sys
{

class SharedDataSystem;
class TimeSystem;

struct InitSystemOptions
{
    bool init_shared_data_system{false};
    bool init_time_system{false};
    bool init_window_system{false};
    bool init_input_system{false};
    bool init_scene_manager{false};
    bool init_resource_manager{false};
    bool init_render_system{false};
    bool init_random_system{false};
    bool init_file_system{false};
    bool init_simulation_system{false};

    void setAllTrue()
    {
        init_shared_data_system = true;
        init_time_system        = true;
        init_window_system      = true;
        init_input_system       = true;
        init_scene_manager      = true;
        init_resource_manager   = true;
        init_render_system      = true;
        init_random_system      = true;
        init_file_system        = true;
        init_simulation_system  = true;
    }
};

template <typename T>
bool getInitSystem(InitSystemOptions const&);

template <>
inline bool getInitSystem<SharedDataSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_shared_data_system;
}

template <>
inline bool getInitSystem<TimeSystem>(
    InitSystemOptions const& init_system_options)
{
    return init_system_options.init_time_system;
}

template <typename T>
inline void setInitSystem(InitSystemOptions &);

template <>
inline void setInitSystem<SharedDataSystem>(
    InitSystemOptions& init_system_options)
{
    init_system_options.init_shared_data_system = true;
}

template <>
inline void setInitSystem<TimeSystem>(
    InitSystemOptions& init_system_options)
{
    init_system_options.init_time_system = true;
}

}  // namespace haf::sys

#endif
