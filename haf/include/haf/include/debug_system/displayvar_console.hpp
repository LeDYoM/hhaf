HTPS_PRAGMA_ONCE
#ifndef HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP
#define HAF_DISPLAY_VAR_CONSOLE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/dictionary.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/debug_system/console.hpp>

namespace haf
{
class DisplayVarConsole : public Console
{
public:
    DisplayVarConsole(htps::rptr<haf::scene::SceneNode> const parent,
                      htps::str name);

    void updateVar(htps::str const& name, htps::s64 const value);
    void update() override;
private:
    using BaseClass = Console;
    htps::PureDictionary m_variables_data;
};
}  // namespace haf

#endif