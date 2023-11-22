HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_MAIN_MESH_CONTROLLER_INCLUDE_HPP
#define HAF_SCENE_MAIN_MESH_CONTROLLER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class MainMeshController final
    : public component::ComponentBootStrap<MainMeshController,
                                           "InternalControllerSubSystem">
{
public:
    static constexpr const haf::core::str_view StaticTypeName{
        "MainMeshController"};

    MainMeshController();
    ~MainMeshController() override;

    void onAttached() override;
    void update();

private:
    bool addRequirements(component::ComponentRequirements&) override;

    struct ComponentsRequired;
    core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;
};

}  // namespace haf::scene

#endif
