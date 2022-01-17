#ifndef HAF_SYSTEM_INIT_SYSTEM_OPTIONS_INCLUDE_HPP
#define HAF_SYSTEM_INIT_SYSTEM_OPTIONS_INCLUDE_HPP

namespace haf::sys
{

struct InitSystemOptions
{
    bool init_debug_system{false};
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
        init_debug_system       = true;
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

}  // namespace haf::sys

#endif
