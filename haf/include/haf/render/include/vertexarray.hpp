#ifndef HAF_SCENE_VERTEXARRAY_INCLUDE_HPP
#define HAF_SCENE_VERTEXARRAY_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/vector.hpp>
#include <haf/render/include/vertex.hpp>
#include <haf/render/include/primitivetype.hpp>

namespace haf::scene
{
using BasicVertexArray = htypes::vector<Vertex>;

/**
 * @brief Low level class representing a vertex array. As needed to render
 * the vertex. It provides some very basic operations too.
 */
class VertexArray
{
public:
    /**
     * @brief Construct a new empty Vertex Array object.
     */
    VertexArray() noexcept;

    explicit VertexArray(const PrimitiveType type) noexcept;

    VertexArray(const PrimitiveType type,
                       const htps::size_type vertexCount) noexcept;

    explicit VertexArray(
        htps::pair<PrimitiveType, htps::size_type> init) noexcept;

    bool empty() const noexcept;

    const BasicVertexArray& verticesArray() const noexcept;
    BasicVertexArray& verticesArray() noexcept;

    PrimitiveType primitiveType() const noexcept;

    void move(const htps::vector2df& offset) noexcept;
    void moveX(const htps::f32 xOffset) noexcept;
    void moveY(const htps::f32 yOffset) noexcept;

private:
    BasicVertexArray m_vertices;
    PrimitiveType m_primitiveType{PrimitiveType::Triangles};
};
}  // namespace haf::scene

#endif
