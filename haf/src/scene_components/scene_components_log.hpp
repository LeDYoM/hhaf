HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_COMPONENTS_SCENE_COMPONENTS_LOG_INCLUDE_HPP
#define HAF_SCENE_COMPONENTS_SCENE_COMPONENTS_LOG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>

namespace haf
{
static constexpr char const SceneComponentsLogMessage[] = "[SceneComponents] ";

struct SceneComponentsLogOptions
    : logger::DefaultMessageLogOptions<SceneComponentsLogMessage>
{};
using SceneComponentsLogDisplayer =
    MessageDisplayLog<SceneComponentsLogOptions>;
}  // namespace haf

#endif
