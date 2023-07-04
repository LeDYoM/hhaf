#include <hogl/include/vao_functions.hpp>
#include "types_private.hpp"
#include <glad/glad.h>
#include <hogl/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::ogl
{
Handle generateVertexArrayObject() noexcept
{
    Handle result{invalidHandle()};
    glCreateVertexArrays(1, &result);
    return result;
}

void deleteVertexArrayObject(Handle const handle) noexcept
{
    glDeleteVertexArrays(1, &handle);
}

void bindVAO(Handle const index) noexcept
{
    glBindVertexArray(index);
}

void bindAttribToBindingIndexForVao(Handle const vao,
                                    Handle const attrib_index,
                                    u32 const numElements,
                                    u32 type_index) noexcept
{
    // We support no offset for buffers
    static constexpr GLuint offset{0U};

    glEnableVertexArrayAttrib(vao, attrib_index);
    glVertexArrayAttribFormat(
        vao, attrib_index, static_cast<GLint>(numElements),
        toOGLEnumType(type_index), GL_FALSE, static_cast<GLuint>(offset));
}

void setbindingIndex(Handle const vao,
                     Handle const attrib_index,
                     Handle const binding_index)
{
    glVertexArrayAttribBinding(vao, attrib_index, binding_index);
}

void disableAttribForVao(Handle const vao, Handle const attrib_index) noexcept
{
    glDisableVertexArrayAttrib(vao, attrib_index);
}

void associateBufferToAttrib(Handle const vao,
                             Handle const binding_index,
                             Handle const buffer_name,
                             s32 const sizeOfStuct) noexcept
{
    glVertexArrayVertexBuffer(vao, binding_index, buffer_name,
                              static_cast<GLintptr>(0), sizeOfStuct);
}

}  // namespace haf::ogl
