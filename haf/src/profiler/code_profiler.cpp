#include <haf/include/profiler/profiler_imp/code_profiler.hpp>

#include <hlog/include/hlog.hpp>
#include "system/get_system.hpp"
#include "time/time_system.hpp"
#include "debug_system/debug_system.hpp"
#include "debug_system/debug_variables.hpp"
#include "debug_system/debug_log.hpp"

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/system/system_access.hpp>
#include <haf/include/system/isystem_provider.hpp>

using namespace htps;

namespace haf::debug
{
CodeProfiler::CodeProfiler(sys::ISystemProvider& isystem_provider,
                           s64& variable_ref,
                           char const* const var_name,
                           std::source_location source) :
    m_system_provider{isystem_provider},
    m_variable_id_ref{variable_ref},
    m_source_location{htps::move(source)},
    m_start{sys::getSystem<sys::TimeSystem>(&m_system_provider).now()}
{
    if (m_variable_id_ref < 0)
    {
        sys::getSystem<sys::DebugSystem>(&m_system_provider)
            .debugVariables()
            .getVariable(m_variable_id_ref, var_name);
    }
}

CodeProfiler::CodeProfiler(scene::SceneNode& scene_node,
                           s64& variable_ref,
                           char const* const var_name,
                           std::source_location source) :
    CodeProfiler{scene_node.isystemProvider(), variable_ref, var_name,
                 htps::move(source)}
{}

CodeProfiler::~CodeProfiler()
{
    auto const time_dif{
        sys::getSystem<sys::TimeSystem>(&m_system_provider).now() - m_start};
    sys::getSystem<sys::DebugSystem>(&m_system_provider)
        .debugVariables()
        .incrementVariable(m_variable_id_ref,
                           static_cast<DebugVariables::DebugVariable_t>(
                               time_dif.nanoseconds()));
}
}  // namespace haf::debug
