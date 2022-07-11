HTPS_PRAGMA_ONCE
#ifndef HAF_PROFILER_CODE_PROFILER_INCLUDE_HPP
#define HAF_PROFILER_CODE_PROFILER_INCLUDE_HPP

#ifdef HAF_PROFILE
#include <haf/include/profiler/profiler_imp/code_profiler.hpp>

#define HAF_PROFILE_SCENE_NODE_METHOD(v_id, text) \
    static htps::s64 variable_id##v_id{-1}; \
    haf::debug::CodeProfiler ___{*this, variable_id##v_id, #text};
#else

#endif

#endif
