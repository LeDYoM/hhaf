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
        render::BufferSubObject const& vertex_buffer_subobject,
        core::vector<core::u32>& associatedAttribsToShader,
        core::u32 const parentHandle,
        core::u32 const parentSizeOfStruct,
        core::u32 const parentSize);

    void disableUnusedAttribsForVaoInShader(
        core::vector<core::u32>& associatedAttribsToShader);

    void associateBuffersToAttribsInCurrentShader(core::sptr<Mesh> mesh);

    ~VertexArrayObjectPriv() noexcept;
};

}  // namespace haf::res
