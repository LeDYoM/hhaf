#ifndef HAF_OGL_VERTEX_ARRAY_FUNCTIONS_INCLUDE_HPP
#define HAF_OGL_VERTEX_ARRAY_FUNCTIONS_INCLUDE_HPP

#include <hogl/include/types.hpp>

namespace haf::ogl
{
Handle generateVertexBufferArray() noexcept;
void bindVAO(Handle const index) noexcept;

void bindAttribToBindingIndexForVao(Handle const vao,
                                    Handle const attrib_index,
                                    Handle const binding_index,
                                    htps::u32 const numElements,
                                    htps::u32 type_index,
                                    htps::u32 offset) noexcept;

void disableAttribForVao(Handle const vao, Handle const attrib_index) noexcept;

void associateBufferToAttrib(Handle const vao,
                             Handle const binding_index,
                             Handle const buffer_name,
                             htps::s32 const sizeOfStuct) noexcept;

}  // namespace haf::ogl

#endif
