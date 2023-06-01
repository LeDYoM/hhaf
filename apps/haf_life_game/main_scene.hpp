#ifndef HF_MAIN_SCENE_INCLUDE_HPP
#define HF_MAIN_SCENE_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace hl
{
class MainScene final : public haf::component::ComponentBootStrap<MainScene>
{
public:
    static constexpr const haf::core::str_view StaticTypeName{"MainScene"};

    MainScene();
    ~MainScene() override;

    void onAttached() override;

private:
    bool addRequirements(haf::component::ComponentRequirements&) override;

    struct ComponentsRequired;
    haf::core::PImplPointer<ComponentsRequired> m_components;
    struct PrivateComponentData;
    haf::core::PImplPointer<PrivateComponentData> m_p;
};
}  // namespace hl

#endif
