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
HOGL_API void attachShader(Handle const program_handle,
                           Handle const shader_handle) noexcept;
HOGL_API void linkProgram(Handle const program_handle) noexcept;
HOGL_API void deleteShader(Handle const shader_handle) noexcept;
HOGL_API void deleteProgram(Handle const program_handle) noexcept;
HOGL_API void useProgram(Handle const program_handle) noexcept;
HOGL_API void clearUseProgram() noexcept;
[[nodiscard]] HOGL_API Handle currentProgram() noexcept;

[[nodiscard]] HOGL_API htps::u32 getNumAttribs(Handle const program) noexcept;
[[nodiscard]] HOGL_API htps::u32 getNumUniforms(Handle const program) noexcept;
[[nodiscard]] HOGL_API htps::u32 getNumUniformBlocks(
    Handle const program) noexcept;

struct GetLowLevelShaderData
{
    htps::s32 location;
    htps::s32 type;
    htps::s32 array_size;
    htps::s32 extra_param0;
    htps::str name;
};

HOGL_API bool getAttribData(Handle const program,
                            htps::u32 const attrib_index,
                            GetLowLevelShaderData& data) noexcept;

HOGL_API bool getUniformData(Handle const program,
                             htps::u32 const uniform_index,
                             GetLowLevelShaderData& data) noexcept;

HOGL_API bool getUniformBlocksData(Handle const program,
                                   htps::u32 const uniform_index,
                                   GetLowLevelShaderData& data) noexcept;

HOGL_API bool getUniformBlocksElementsData(
    Handle const program,
    htps::u32 const uniform_index,
    GetLowLevelShaderData& data) noexcept;

HOGL_API void bindAttributeIndex(Handle const program,
                                 htps::u32 const index,
                                 htps::str_view const name) noexcept;

HOGL_API void bindUniformBlockIndex(Handle const program,
                                    htps::u32 const index,
                                    htps::u32 const bindingPoint) noexcept;

}  // namespace haf::ogl

#endif
