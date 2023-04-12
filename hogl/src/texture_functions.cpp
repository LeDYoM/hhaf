#include <hogl/include/texture_functions.hpp>
#include <glad/glad.h>

using namespace htps;

namespace haf::ogl
{
Handle createTexture() noexcept
{
    Handle result{ogl::invalidHandle()};
    glCreateTextures(GL_TEXTURE_2D, 1, &result);
    return result;
}

void destroyTexture(Handle const handle) noexcept
{
    glDeleteTextures(1, &handle);
}

}  // namespace haf::ogl