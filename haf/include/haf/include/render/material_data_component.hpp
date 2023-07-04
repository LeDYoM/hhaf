HAF_PRAGMA_ONCE
#ifndef HAF_RENDER_MATERIAL_DATA_COMPONENT_INCLUDE_HPP
#define HAF_RENDER_MATERIAL_DATA_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <facil_math/include/matrix4x4.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::render
{
class HAF_API MaterialDataComponent final
    : public component::ComponentBootStrap<MaterialDataComponent>
{
public:
    MaterialDataComponent();
    ~MaterialDataComponent();

    static constexpr const core::str_view StaticTypeName{"MaterialDataComponent"};

private:
    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;

    void onAttached() override;
    bool addRequirements(component::ComponentRequirements&) override;
};

}  // namespace haf::render

#endif
