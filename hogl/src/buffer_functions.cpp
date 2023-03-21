#include <hogl/include/buffer_functions.hpp>
#include "types_private.hpp"
#include <glad/glad.h>
#include <hogl/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::ogl
{
Handle createRenderBuffer(void const* const data, s32 const size)
{
    Handle result{invalidHandle()};
    glCreateBuffers(1, &result);
    glNamedBufferData(result, static_cast<GLsizeiptr>(size), data,
                      GL_STATIC_DRAW);

    return result;
}

}  // namespace haf::ogl
