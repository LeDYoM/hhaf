HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_MESH_COMPONENT_INCLUDE_HPP
#define HAF_RENDER_MESH_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::scene
{
class TransformationComponent;
}
namespace haf::render
{
class MeshRenderContext;
class MeshRenderComponent;

class HAF_API MeshComponent final
    : public component::ComponentBase<"MeshComponent",
                                      MeshRenderComponent,
                                      scene::TransformationComponent>
{
public:
    void onAttached() override;

private:
    core::sptr<MeshRenderContext> m_renderContext;
};

}  // namespace haf::render

#endif
