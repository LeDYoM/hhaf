#include "vertex_array_object_private.hpp"
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hogl/include/vao_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "default_shader_data.hpp"
#include <glad/glad.h>

using namespace haf::core;

namespace haf::res
{
void VertexArrayObject::VertexArrayObjectPriv::
    associateBuffersToAttribsInCurrentShader(sptr<Mesh> mesh)
{
    u32 binding_index{0U};
    vector<u32> currentAssociatedAttribsToShaderForVao(
        mesh->vertexBufferObjects().size());
    for (auto const& vertex_buffer_object : mesh->vertexBufferObjects())
    {
        associateBufferToAttib(binding_index++,
                               vertex_buffer_object->subObject(),
                               currentAssociatedAttribsToShaderForVao,
                               vertex_buffer_object->handle(),
                               vertex_buffer_object->vertexFormatSize(),
                               vertex_buffer_object->size());
    }
    disableUnusedAttribsForVaoInShader(currentAssociatedAttribsToShaderForVao);
}

void VertexArrayObject::VertexArrayObjectPriv::associateBufferToAttib(
    u32 const binding_index,
    render::BufferSubObject const& vertex_buffer_subobject,
    vector<u32>& associatedAttribsToShader,
    u32 const parentHandle,
    u32 const parentSizeOfStruct,
    u32 const parentSize)
{
    // TODO: We could check that the buffer to associate has the correct
    s32 const expected_index{m_shader->m_shader_metadata.attributeIndex(
        str_view{vertex_buffer_subobject.index().c_str()})};
    if (expected_index > -1)
    {
        ogl::bindAttribToBindingIndexForVao(
            m_vao, static_cast<ogl::Handle>(expected_index),
            vertex_buffer_subobject.vertexFormat().numElements,
            static_cast<core::u32>(
                vertex_buffer_subobject.vertexFormat().bufferType));
        ogl::setbindingIndex(m_vao, static_cast<ogl::Handle>(expected_index),
                             binding_index);

        associatedAttribsToShader.push_back(static_cast<u32>(expected_index));
        DisplayLog::debug("Associating buffer ", expected_index);
        DisplayLog::debug("\t To binding index: ", binding_index);
    }

    ogl::associateBufferToAttrib(m_vao, binding_index, parentHandle,
                                 parentSizeOfStruct);

    m_size = parentSize;
}

void VertexArrayObject::VertexArrayObjectPriv::
    disableUnusedAttribsForVaoInShader(vector<u32>& associatedAttribsToShader)
{
    auto const unused_attribs_in_shader{
        m_shader->m_shader_metadata.unusedAttribs(associatedAttribsToShader)};
    for (auto&& unused_attrib_in_shader : unused_attribs_in_shader)
    {
        ogl::disableAttribForVao(m_vao, unused_attrib_in_shader.second);
    }
}

void VertexArrayObject::VertexArrayObjectPriv::render()
{
    ogl::bindVAO(m_vao);
    glBindTextureUnit(0, 1);
    m_shader->bind();
    glDrawArrays(GL_TRIANGLES, 0, m_size);
    ogl::bindVAO(ogl::invalidHandle());
}

VertexArrayObject::VertexArrayObjectPriv::~VertexArrayObjectPriv() noexcept
{
    if (m_vao != ogl::invalidHandle())
    {
        ogl::deleteVertexArrayObject(m_vao);
    }
}

}  // namespace haf::res
