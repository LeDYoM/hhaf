#ifndef HAF_BACKEND_OPENGL_GL_CHECK_INCLUDE_HPP
#define HAF_BACKEND_OPENGL_GL_CHECK_INCLUDE_HPP
#define OPENGL_CHECK_DEBUG

#ifdef OPENGL_CHECK_DEBUG

#define glCheck(expr) \
    {   \
        expr; \
        haf::backend::ogl::glCheckError(__FILE__, __LINE__, #expr); \
    }
#else
#define glCheck(expr) { expr; }
#endif

namespace haf::backend::ogl
{
void glCheckError(const char* file, unsigned int line, const char* expression);
}

#endif  // SFML_GLCHECK_HPP
