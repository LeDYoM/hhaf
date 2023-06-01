HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_MESH_RENDER_COMPONENT_INCLUDE_HPP
#define HAF_RENDER_MESH_RENDER_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>

#include <haf/include/resources/shader.hpp>

namespace haf::render
{
class HAF_API MeshRenderComponent final
    : public component::ComponentBootStrap<MeshRenderComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{"MeshRenderComponent"};

    MeshRenderComponent();
    ~MeshRenderComponent();

    void onAttached() override;
    void updateRender();

    core::sptr<res::Shader> shader() const noexcept;
private:
    struct PrivateComponentData;
    core::PImplPointer<PrivateComponentData> m_p;
};

}  // namespace haf::render

#endif
