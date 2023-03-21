#ifndef HAF_OGL_SHADER_INCLUDE_HPP
#define HAF_OGL_SHADER_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::ogl
{
[[nodiscard]] HOGL_API Handle createFragmentShader() noexcept;
[[nodiscard]] HOGL_API Handle createVertexShader() noexcept;
[[nodiscard]] HOGL_API bool compileShader(Handle const handle,
                                 htps::str_view const code) noexcept;
[[nodiscard]] HOGL_API Handle createProgram() noexcept;
void HOGL_API attachShader(Handle const program_handle,
                  Handle const shader_handle) noexcept;
void HOGL_API linkProgram(Handle const program_handle) noexcept;
void HOGL_API deleteShader(Handle const shader_handle) noexcept;
void HOGL_API deleteProgram(Handle const program_handle) noexcept;
void HOGL_API useProgram(Handle const program_handle) noexcept;
void HOGL_API clearUseProgram() noexcept;
[[nodiscard]] HOGL_API Handle currentProgram() noexcept;

[[nodiscard]] HOGL_API htps::u32 getNumAttribs(Handle const program) noexcept;
[[nodiscard]] HOGL_API htps::u32 getNumUniforms(Handle const program) noexcept;

bool HOGL_API getAttribData(Handle const program,
                   htps::u32 const attrib_index,
                   htps::s32& location,
                   htps::s32& attrib_type,
                   htps::s32& attrib_array_size,
                   htps::str& name) noexcept;

bool HOGL_API getUniformData(Handle const program,
                    htps::u32 const uniform_index,
                    htps::s32& location,
                    htps::s32& uniform_type,
                    htps::s32& uniform_array_size,
                    htps::str& name) noexcept;

void HOGL_API bindAttributeIndex(Handle const program,
                        htps::u32 const index,
                        htps::str_view const name) noexcept;

}  // namespace haf::ogl

#endif
