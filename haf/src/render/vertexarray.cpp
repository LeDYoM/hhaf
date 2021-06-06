#include <haf/include/render/vertexarray.hpp>

using namespace htps;

namespace haf::scene
{

VertexArray::VertexArray() noexcept = default;

VertexArray::VertexArray(const PrimitiveType type) noexcept :
    m_vertices(), m_primitiveType{type}
{}

VertexArray::VertexArray(const PrimitiveType type,
                   const htps::size_type vertexCount) noexcept :
    m_vertices(vertexCount), m_primitiveType{type}
{}

VertexArray::VertexArray(
    htps::pair<PrimitiveType, htps::size_type> init) noexcept :
    VertexArray{init.first, init.second}
{}

bool VertexArray::empty() const noexcept
{
    return m_vertices.empty();
}

const BasicVertexArray& VertexArray::verticesArray() const noexcept
{
    return m_vertices;
}

BasicVertexArray& VertexArray::verticesArray() noexcept
{
    return m_vertices;
}

PrimitiveType VertexArray::primitiveType() const noexcept
{
    return m_primitiveType;
}

void VertexArray::move(const vector2df& offset) noexcept
{
    for (auto& v : m_vertices)
        v.position += offset;
}

void VertexArray::moveX(const f32 xOffset) noexcept
{
    for (auto& v : m_vertices)
        v.position.x += xOffset;
}

void VertexArray::moveY(const f32 yOffset) noexcept
{
    for (auto& v : m_vertices)
        v.position.y += yOffset;
}
}  // namespace haf::scene
