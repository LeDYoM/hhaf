#include <hogl/include/render_system_functions.hpp>
#include <glad/glad.h>
#include <hogl/include/types.hpp>
#include <hlog/include/hlog.hpp>

using namespace fmath;

void APIENTRY message_callback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam)
{
    (void)(length);
    (void)(userParam);
    auto const src_str = [source]() {
        switch (source)
        {
            case GL_DEBUG_SOURCE_API:
                return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION:
                return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER:
                return "OTHER";
        }
        return "";
    }();

    auto const type_str = [type]() {
        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:
                return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY:
                return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE:
                return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER:
                return "MARKER";
            case GL_DEBUG_TYPE_OTHER:
                return "OTHER";
        }
        return "";
    }();

    auto const severity_str = [severity]() {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW:
                return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM:
                return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH:
                return "HIGH";
        }
        return "";
    }();
    haf::DisplayLog::debug("[RenderSystem] ", src_str, ", ", type_str, ", ",
                           severity_str, ", ", id, ": ", message);
}

namespace haf::ogl
{
bool initOGL()
{
    int const result{gladLoadGL()};
    return result != 0;
}

void setDebug(bool const enable)
{
    if (enable)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(message_callback, nullptr);
    }
    else
    {
        glDisable(GL_DEBUG_OUTPUT);
    }
}

void setDefaultRenderState()
{
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void clearBackgroundColor(vector4df const& color)
{
    glClearBufferfv(GL_COLOR, 0, &color.x);
}

void clearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

}  // namespace haf::ogl
