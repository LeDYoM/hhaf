#include <hogl/include/vertex_buffer.hpp>
#include "opengl/glad.h"
#include "opengl/gl_check.hpp"

static_assert(std::is_same_v<GLuint, haf::ogl::NativeHandleType>,
              "GLuint and size_type should be the same type");

inline bool validNativeHandle(haf::ogl::NativeHandleType const nht) noexcept
{
    return nht != 0U;
}

using namespace htps;
using namespace haf::backend;

namespace
{
using namespace haf::ogl;

GLenum usageToGlEnum(VertexBuffer::Usage const usage)
{
    switch (usage)
    {
        case VertexBuffer::Usage::Static:
            return GL_STATIC_DRAW;
        case VertexBuffer::Usage::Dynamic:
            return GL_DYNAMIC_DRAW;
        case VertexBuffer::Usage::Stream:
        default:
            return GL_STREAM_DRAW;
    }
}
}  // namespace

namespace haf::ogl
{
VertexBuffer::VertexBuffer(VertexBuffer::Usage const usage) :
    m_buffer{0U}, m_size{0U}, m_usage{usage}
{}

VertexBuffer::~VertexBuffer()
{
    if (validNativeHandle(m_buffer))
    {
        glCheck(glDeleteBuffers(1, &m_buffer));
    }
}

bool VertexBuffer::create(size_type const vertexCount)
{
    if (!validNativeHandle(m_buffer))
    {
        glCheck(glGenBuffers(1, &m_buffer));
    }

    if (!validNativeHandle(m_buffer))
    {
        return false;
    }

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_buffer));
    glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, 0,
                         usageToGlEnum(m_usage)));
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

    m_size = vertexCount;

    return true;
}

size_type VertexBuffer::getVertexCount() const noexcept
{
    return m_size;
}

bool VertexBuffer::update(Vertex const* const vertices)
{
    return update(vertices, m_size, 0);
}

bool VertexBuffer::update(Vertex const* const vertices,
                          size_type const vertexCount,
                          size_type const offset)
{
    // Sanity checks
    if (!validNativeHandle(m_buffer))
    {
        return false;
    }

    if (!vertices)
    {
        return false;
    }

    if (offset && (offset + vertexCount > m_size))
    {
        return false;
    }

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_buffer));

    // Check if we need to resize or orphan the buffer
    if (vertexCount >= m_size)
    {
        glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, 0,
                             usageToGlEnum(m_usage)));

        m_size = vertexCount;
    }

    glCheck(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex) * offset,
                            sizeof(Vertex) * vertexCount, vertices));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return true;
}

NativeHandleType VertexBuffer::getNativeHandle() const noexcept
{
    return m_buffer;
}

void VertexBuffer::setUsage(VertexBuffer::Usage const usage) noexcept
{
    m_usage = usage;
}

VertexBuffer::Usage VertexBuffer::getUsage() const noexcept
{
    return m_usage;
}

}  // namespace haf::ogl
