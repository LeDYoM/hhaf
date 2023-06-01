#ifndef HF_MAIN_MESH_CONTROLLER_INCLUDE_HPP
#define HF_MAIN_MESH_CONTROLLER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace hl
{
class MainMeshController final
    : public haf::component::ComponentBootStrap<MainMeshController>
{
public:
    static constexpr const haf::core::str_view StaticTypeName{
        "MainMeshController"};

    MainMeshController();
    ~MainMeshController() override;

    void onAttached() override;
    void update();

private:
    bool addRequirements(haf::component::ComponentRequirements&) override;

    struct ComponentsRequired;
    haf::core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    haf::core::PImplPointer<PrivateComponentData> m_p;
};

}  // namespace hl

#endif
