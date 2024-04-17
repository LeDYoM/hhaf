HAF_PRAGMA_ONCE
#ifndef HAF_DEBUG_DEBUGABLE_COMPONENT_INCLUDE_HPP
#define HAF_DEBUG_DEBUGABLE_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>
#include <haf/include/input/key.hpp>

namespace haf::debug
{
class HAF_API DebugComponent final
    : public component::ComponentBootStrap<DebugComponent, "RenderSubSystem">
{
public:
    static constexpr const core::str_view StaticTypeName{"DebugComponent"};

    DebugComponent();
    ~DebugComponent();

    void onAttached() override;

private:
    void onKeyPressed(input::Key const& key);
};

}  // namespace haf::debug

#endif