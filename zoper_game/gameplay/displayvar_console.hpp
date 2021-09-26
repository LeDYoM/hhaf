#ifndef HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP
#define HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/scenenode.hpp>
#include "console.hpp"

namespace haf
{
class DisplayVarConsole : public Console
{
public:
    DisplayVarConsole(htps::rptr<haf::scene::SceneNode> const parent,
                      htps::str name);
};
}  // namespace haf

#endif