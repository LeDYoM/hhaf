HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCEMANAGER_DEFAULT_RESOURCES_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_DEFAULT_RESOURCES_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/shader.hpp>
#include <haf/include/resources/vertex_buffer_object.hpp>
#include <haf/include/resources/vertex_array_object.hpp>

namespace haf::sys
{
class ResourceManager;
}
namespace haf::res
{
class DefaultResources final
{
public:
    bool loadDefaultResources(sys::ResourceManager& rManager);
    core::sptr<Shader> getDefaultShaderNoInput() const;
    core::sptr<Shader> getDefaultShader0() const;
    core::sptr<VertexBufferObject> getDefaultPositionRenderDataBufer() const;
    core::sptr<VertexBufferObject> getDefaultColorRenderDataBufer() const;

private:
    bool loadDefaultShaderNoInput(sys::ResourceManager& rManager);
    bool loadDefaultShader0(sys::ResourceManager& rManager);
    bool loadDefaultBuffers(sys::ResourceManager& rManager);
    bool loadDefaultMesh(sys::ResourceManager& rManager);
    bool loadDefaultVertexArrayObject(sys::ResourceManager& rManager);
    bool loadDefaultCubeMesh(sys::ResourceManager& rManager);

    core::sptr<Shader> m_defaultShaderNoInput;
    core::sptr<Shader> m_defaultShader0;
    core::sptr<VertexBufferObject> m_defaultPositions;
    core::sptr<VertexBufferObject> m_defaultColors;
    core::sptr<VertexBufferObject> m_quadPositions;
    core::sptr<VertexBufferObject> m_quadColors;
};

}  // namespace haf::res

#endif
