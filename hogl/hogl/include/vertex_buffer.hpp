#ifndef HAF_OGL_VERTEX_BUFFER_INCLUDE_HPP
#define HAF_OGL_VERTEX_BUFFER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "backend_dev/include/ivertex.hpp"

namespace haf::ogl
{
using NativeHandleType = htps::u32;

class VertexBuffer
{
public:
    enum Usage
    {
        Stream,   ///< Constantly changing data
        Dynamic,  ///< Occasionally changing data
        Static    ///< Rarely changing data
    };

    explicit VertexBuffer(Usage const usage);

    ~VertexBuffer();

    bool create(htps::size_type const vertexCount);

    htps::size_type getVertexCount() const noexcept;

    bool update(backend::Vertex const* const vertices);

    bool update(backend::Vertex const* const vertices,
                htps::size_type const vertexCount,
                htps::size_type const offset);

    NativeHandleType getNativeHandle() const noexcept;

    void setUsage(Usage const usage) noexcept;

    Usage getUsage() const noexcept;

private:
    NativeHandleType m_buffer;
    htps::size_type m_size;
    Usage m_usage;
};

}  // namespace haf::backend::ogl

#endif
