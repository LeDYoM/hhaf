#include <haf/include/resources/vertex_array_object.hpp>
#include <hogl/include/types.hpp>

namespace haf::res
{
struct VertexArrayObject::VertexArrayObjectPriv
{
    ogl::Handle m_vao;
    core::sptr<Mesh> m_mesh;
    core::sptr<Shader> m_shader;
    core::u32 m_size;

    void associateBufferToAttib(
        core::u32 const binding_index,
        core::vector<VertexBufferSubObject> const& vertex_buffer_subobjects,
        core::vector<core::u32>& associatedAttribsToShader);

    void disableUnusedAttribsForVaoInShader(
        core::vector<core::u32>& associatedAttribsToShader);

    void render();
};

}  // namespace haf::res
