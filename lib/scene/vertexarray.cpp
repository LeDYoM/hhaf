#include "vertexarray.hpp"

namespace lib::scene
{
    void VertexArray::move(const vector2df & offset) noexcept
    {
        for (auto &v : m_vertices) v.position += offset;
    }

    void VertexArray::moveX(const f32 xOffset) noexcept
    {
        for (auto &v : m_vertices) v.position.x += xOffset;
    }

    void VertexArray::moveY(const f32 yOffset) noexcept
    {
        for (auto &v : m_vertices) v.position.y += yOffset;
    }
}
