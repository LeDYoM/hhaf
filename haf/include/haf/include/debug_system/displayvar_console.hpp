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
private:
    using BaseClass = Console;
public:
    using BaseClass::BaseClass;
    void updateVar(htps::str const& name, htps::s64 const value);
    void update() override;
private:
    htps::PureDictionary m_variables_data;
};
}  // namespace haf

#endif