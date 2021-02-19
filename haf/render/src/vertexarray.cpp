#include <haf/render/include/vertexarray.hpp>

using namespace htps;

namespace haf::scene
{
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
