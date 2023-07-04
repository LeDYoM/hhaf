#ifndef HAF_OGL_VERTEX_ARRAY_FUNCTIONS_INCLUDE_HPP
#define HAF_OGL_VERTEX_ARRAY_FUNCTIONS_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <hogl/include/types.hpp>

namespace haf::ogl
{
[[nodiscard]] HOGL_API Handle generateVertexArrayObject() noexcept;
HOGL_API void deleteVertexArrayObject(Handle const handle) noexcept;
HOGL_API void bindVAO(Handle const index) noexcept;

HOGL_API void bindAttribToBindingIndexForVao(Handle const vao,
                                             Handle const attrib_index,
                                             htps::u32 const numElements,
                                             htps::u32 type_index) noexcept;

HOGL_API void setbindingIndex(Handle const vao,
                              Handle const attrib_index,
                              Handle const binding_index);

HOGL_API void disableAttribForVao(Handle const vao,
                                  Handle const attrib_index) noexcept;

HOGL_API void associateBufferToAttrib(Handle const vao,
                                      Handle const binding_index,
                                      Handle const buffer_name,
                                      htps::s32 const sizeOfStuct) noexcept;

}  // namespace haf::ogl

#endif
