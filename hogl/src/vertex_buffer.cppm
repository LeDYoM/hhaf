module;

#include <hogl/opengl/glad.h>
#include "opengl/gl_check.hpp"

export module hogl:vertex_buffer;

import backend_dev;
import htypes;

static_assert(std::is_same_v<GLuint, haf::ogl::NativeHandleType>,
              "GLuint and size_type should be the same type");

constexpr bool validNativeHandle(haf::ogl::NativeHandleType const nht) noexcept
{
    return nht != 0U;
}

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

namespace haf::ogl
{
using NativeHandleType = htps::u32;

export class VertexBuffer
{
public:
    enum class Usage
    {
        Stream,   ///< Constantly changing data
        Dynamic,  ///< Occasionally changing dataF
        Static    ///< Rarely changing data
    };

    explicit VertexBuffer(Usage const usage) noexcept :
        m_buffer{0U}, m_size{0U}, m_usage{usage}
    {}

    ~VertexBuffer() noexcept
    {
        if (validNativeHandle(m_buffer))
        {
            glCheck(glDeleteBuffers(1, &m_buffer));
        }
    }

    bool create(htps::size_type const vertexCount) noexcept
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

    inline htps::size_type getVertexCount() const noexcept { return m_size; }

    bool update(backend::Vertex const* const vertices)
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
            glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount,
                                 0, usageToGlEnum(m_usage)));

            m_size = vertexCount;
        }

        glCheck(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex) * offset,
                                sizeof(Vertex) * vertexCount, vertices));

        glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

        return true;
    }

    bool update(backend::Vertex const* const vertices,
                htps::size_type const vertexCount,
                htps::size_type const offset)
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
            glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount,
                                 0, usageToGlEnum(m_usage)));

            m_size = vertexCount;
        }

        glCheck(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex) * offset,
                                sizeof(Vertex) * vertexCount, vertices));

        glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));

        return true;
    }

    NativeHandleType getNativeHandle() const noexcept { return m_buffer; }

    void setUsage(Usage const usage) noexcept { m_usage = usage; }

    Usage getUsage() const noexcept { return m_usage; }

private:
    NativeHandleType m_buffer;
    htps::size_type m_size;
    Usage m_usage;
};

}  // namespace haf::ogl
