HTPS_PRAGMA_ONCE
#ifndef HAF_PROFILER_CODE_PROFILER_INCLUDE_HPP
#define HAF_PROFILER_CODE_PROFILER_INCLUDE_HPP

#ifdef HAF_PROFILE
#include <haf/include/profiler/profiler_imp/code_profiler.hpp>
#include <haf/include/debug_system/debug_types.hpp>

#define HAF_PROFILE_SCENE_NODE_METHOD(v_id) \
    HAF_DECLARE_DEBUG_VARIABLE(v_id)    \
    haf::debug::CodeProfiler ___{*this, HAF_DEBUG_VARIABLE_NAME(v_id), #v_id};
#else

#endif

#endif
