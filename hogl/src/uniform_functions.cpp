#include <hogl/include/uniform_functions.hpp>
#include "types_private.hpp"
#include <glad/glad.h>
#include <hogl/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::ogl
{
void setMatrixUniform(ogl::Handle const program,
                      s32 const location,
                      s32 const size,
                      bool const transpose,
                      f32 const* const data) noexcept
{
    glProgramUniformMatrix4fv(program, location, size,
                              transpose ? GL_TRUE : GL_FALSE, data);
}

}  // namespace haf::ogl
