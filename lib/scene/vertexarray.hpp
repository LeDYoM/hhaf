#pragma once

#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>
#include <mtypes/include/properties.hpp>

namespace lib::scene
{
using BasicVertexArray = vector<Vertex>;

enum class PrimitiveType : u8
{
    Points = 0U,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan
};

class VertexArray
{
public:
    constexpr VertexArray() noexcept = default;
    explicit constexpr VertexArray(const PrimitiveType type) noexcept
        : m_vertices(), m_primitiveType{type} {}

    inline VertexArray(
        const PrimitiveType type,
        const size_type vertexCount) noexcept
        : m_vertices(vertexCount), m_primitiveType{type} {}

    explicit inline VertexArray(
        pair<PrimitiveType, size_type> init) noexcept
        : VertexArray{init.first, init.second} {}

    constexpr bool empty() const noexcept { return m_vertices.empty(); }

    constexpr const BasicVertexArray &verticesArray() const noexcept { return m_vertices; }
    constexpr BasicVertexArray &verticesArray() noexcept { return m_vertices; }

    constexpr PrimitiveType primitiveType() const noexcept { return m_primitiveType; }

    void move(const vector2df &offset) noexcept;
    void moveX(const f32 xOffset) noexcept;
    void moveY(const f32 yOffset) noexcept;

private:
    BasicVertexArray m_vertices;
    PrimitiveType m_primitiveType{PrimitiveType::Triangles};
};
} // namespace lib::scene

#endif
