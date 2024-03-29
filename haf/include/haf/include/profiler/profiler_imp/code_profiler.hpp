HTPS_PRAGMA_ONCE
#ifndef HAF_PROFILER_CODE_PROFILER_IMP_INCLUDE_HPP
#define HAF_PROFILER_CODE_PROFILER_IMP_INCLUDE_HPP

#include <source_location>
#include <haf/include/time/time_point.hpp>

namespace haf::sys
{
class ISystemProvider;
}

namespace haf::scene
{
class SceneNode;
}

namespace haf::debug
{
class CodeProfiler
{
public:
    CodeProfiler(sys::ISystemProvider& isystem_provider,
                 htps::s64& variable_ref, char const * const var_name,
                 std::source_location source = std::source_location::current());

    CodeProfiler(scene::SceneNode& scene_node,
                 htps::s64& variable_ref, char const * const var_name,
                 std::source_location source = std::source_location::current());

    ~CodeProfiler();

private:
    sys::ISystemProvider& m_system_provider;
    htps::s64& m_variable_id_ref;
    std::source_location m_source_location;
    time::TimePoint m_start;
};
}  // namespace haf::debug

#define HAF_PROFILE_FUNCTION

#endif
