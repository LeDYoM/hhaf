#ifndef HAF_OGL_BUFFER_FUNCTIONS_INCLUDE_HPP
#define HAF_OGL_BUFFER_FUNCTIONS_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/span.hpp>

namespace haf::ogl
{
enum class HOGL_API BufferUsage : htps::u32
{
    Static  = 0U,
    Dynamic = 1U
};

enum class HOGL_API BufferMode : htps::u32
{
    Draw = 0U,
};

[[nodiscard]] HOGL_API Handle createRenderBuffer(void const* const data,
                                                 htps::s32 const size,
                                                 BufferUsage const bufferUsage,
                                                 BufferMode const bufferMode);

[[nodiscard]] HOGL_API void* getAddressForWriting(Handle const index,
                                                  htps::s32 const size);
HOGL_API void unlock(Handle const index);
HOGL_API void bindBufferUniformBlock(Handle const bindingPoint,
                                                   Handle const bufferUniform);

}  // namespace haf::ogl

#endif
