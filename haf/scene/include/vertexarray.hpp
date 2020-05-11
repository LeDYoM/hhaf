#pragma once

#ifndef HAF_SCENE_VERTEXARRAY_INCLUDE_HPP
#define HAF_SCENE_VERTEXARRAY_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/properties.hpp>
#include <haf/scene/include/vertex.hpp>
#include <haf/scene/include/primitivetype.hpp>

namespace haf::scene
{
using BasicVertexArray = mtps::vector<Vertex>;

class VertexArray
{
public:
    constexpr VertexArray() noexcept = default;
    explicit constexpr VertexArray(const PrimitiveType type) noexcept
        : m_vertices(), m_primitiveType{type} {}

    inline VertexArray(
        const PrimitiveType type,
        const mtps::size_type vertexCount) noexcept
        : m_vertices(vertexCount), m_primitiveType{type} {}

    explicit inline VertexArray(
        mtps::pair<PrimitiveType, mtps::size_type> init) noexcept
        : VertexArray{init.first, init.second} {}

    constexpr bool empty() const noexcept { return m_vertices.empty(); }

    constexpr const BasicVertexArray &verticesArray() const noexcept { return m_vertices; }
    constexpr BasicVertexArray &verticesArray() noexcept { return m_vertices; }

    constexpr PrimitiveType primitiveType() const noexcept { return m_primitiveType; }

    void move(const mtps::vector2df &offset) noexcept;
    void moveX(const mtps::f32 xOffset) noexcept;
    void moveY(const mtps::f32 yOffset) noexcept;

private:
    BasicVertexArray m_vertices;
    PrimitiveType m_primitiveType{PrimitiveType::Triangles};
};
} // namespace haf::scene

#endif
