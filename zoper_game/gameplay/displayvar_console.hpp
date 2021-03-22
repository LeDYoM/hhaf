#ifndef HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP
#define HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/scene/include/scenenode.hpp>

namespace zoper
{
class DisplayVarConsole : public haf::scene::SceneNode
{
public:
    DisplayVarConsole(htps::rptr<haf::scene::SceneNode> const parent,
                     htps::str name);
    ~DisplayVarConsole() override;

    void init();
};
}  // namespace zoper

#endif