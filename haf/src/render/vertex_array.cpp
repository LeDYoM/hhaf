#include <haf/include/render/vertex_array.hpp>

using namespace htps;
using namespace haf::scene;

namespace haf::render
{

VertexArray::VertexArray() noexcept = default;

VertexArray::VertexArray(const PrimitiveType type) noexcept :
    vertices_(), primitive_type_{type}
{}

VertexArray::VertexArray(const PrimitiveType type,
                         const htps::size_type vertexCount) noexcept :
    vertices_(vertexCount), primitive_type_{type}
{}

VertexArray::VertexArray(
    htps::pair<PrimitiveType, htps::size_type> init) noexcept :
    VertexArray{init.first, init.second}
{}

bool VertexArray::empty() const noexcept
{
    return vertices_.empty();
}

const BasicVertexArray& VertexArray::verticesArray() const noexcept
{
    return vertices_;
}

BasicVertexArray& VertexArray::verticesArray() noexcept
{
    return vertices_;
}

PrimitiveType VertexArray::primitiveType() const noexcept
{
    return primitive_type_;
}

void VertexArray::move(const vector2df& offset) noexcept
{
    for (auto& v : vertices_)
        v.position += offset;
}

void VertexArray::moveX(const f32 xOffset) noexcept
{
    for (auto& v : vertices_)
        v.position.x += xOffset;
}

void VertexArray::moveY(const f32 yOffset) noexcept
{
    for (auto& v : vertices_)
        v.position.y += yOffset;
}
}  // namespace haf::render
