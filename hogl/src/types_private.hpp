#ifndef HAF_OGL_TYPES_PRIVATE_INCLUDE_HPP
#define HAF_OGL_TYPES_PRIVATE_INCLUDE_HPP

#include <hogl/include/types.hpp>
#include <glad/glad.h>

namespace haf::ogl
{
constexpr auto toOGLEnumType(htps::u32 const index)
{
    switch (index)
    {
        case 1:
            return GL_FLOAT;
            break;
    }
    return 0;
}

constexpr htps::u32 fromOGLEnumType(GLenum const index)
{
    switch (index)
    {
        case GL_FLOAT:
            return 1U;
            break;
    }
    return 0U;
}

}  // namespace haf::ogl

#endif
