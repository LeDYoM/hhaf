#include <hogl/include/buffer_functions.hpp>
#include "types_private.hpp"
#include <glad/glad.h>
#include <hogl/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace
{
constexpr GLenum fromUsageAndMode(
    haf::ogl::BufferUsage const bufferUsage,
    haf::ogl::BufferMode const bufferMode) noexcept
{
    if (bufferUsage == haf::ogl::BufferUsage::Static)
    {
        if (bufferMode == haf::ogl::BufferMode::Draw)
        {
            return GL_STATIC_DRAW;
        }
        // Static default
        return GL_STATIC_DRAW;
    }
    else if (bufferUsage == haf::ogl::BufferUsage::Dynamic)
    {
        if (bufferMode == haf::ogl::BufferMode::Draw)
        {
            return GL_DYNAMIC_DRAW;
        }
        // Dynamic default
        return GL_DYNAMIC_DRAW;
    }

    // Dummy default
    return GL_STATIC_DRAW;
}
}  // namespace

namespace haf::ogl
{
Handle createRenderBuffer(void const* const data,
                          s32 const size,
                          BufferUsage const bufferUsage,
                          BufferMode const bufferMode)
{
    Handle result{invalidHandle()};
    glCreateBuffers(1, &result);
    glNamedBufferData(result, static_cast<GLsizeiptr>(size), data,
                      fromUsageAndMode(bufferUsage, bufferMode));

    return result;
}

void* getAddressForWriting(Handle const index, s32 const size)
{
    return glMapNamedBufferRange(
        index, 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
}

void unlock(Handle const index)
{
    glUnmapNamedBuffer(index);
}

void bindBufferUniformBlock(Handle const bindingPoint,
                            Handle const bufferUniform)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, bufferUniform);
}

}  // namespace haf::ogl
