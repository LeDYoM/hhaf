#ifndef HAF_SCENE_VERTEXARRAY_INCLUDE_HPP
#define HAF_SCENE_VERTEXARRAY_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/properties.hpp>
#include <htypes/include/vector.hpp>
#include <haf/include/render/vertex.hpp>
#include <haf/include/render/primitivetype.hpp>

namespace haf::scene
{
using BasicVertexArray = htps::vector<Vertex>;

/**
 * @brief Low level class representing a vertex array. As needed to render
 * the vertex. It provides some very basic operations too. It also stores the
 * primitive used to paint it.
 * @see PrimitiveType
 */
class VertexArray
{
public:
    /**
     * @brief Construct a new empty Vertex Array object.
     */
    VertexArray() noexcept;

    /**
     * @brief Construct a new Vertex Array object from a primitve type
     * The vertex array will be empty.
     * @param type Primitivetype that the object will conrain
     */
    explicit VertexArray(const PrimitiveType type) noexcept;

    /**
     * @brief Construct a new Vertex Array object from a primitve type and
     * a size.
     * @param type Primitivetype that the object will conrain
     * @param vertexCount Number of vertex in the object
     */
    VertexArray(const PrimitiveType type,
                const htps::size_type vertexCount) noexcept;

    /**
     * @brief Construct a new Vertex Array object from a pair
     * containing the primitive type and the size
     * @param init Parameter containing these two data elements
     */
    explicit VertexArray(
        htps::pair<PrimitiveType, htps::size_type> init) noexcept;

    /**
     * @brief Ask if the object is empty or not.
     * @return true The object is empty
     * @return false The object contains at least one vertex
     */
    bool empty() const noexcept;

    /**
     * @brief Getter for the inner container of vertex. Const version
     * @return const BasicVertexArray& The inner container of the object
     */
    const BasicVertexArray& verticesArray() const noexcept;

    /**
     * @brief Getter for the inner container of vertex. Non const version
     * @return const BasicVertexArray& The inner container of the object
     */
    BasicVertexArray& verticesArray() noexcept;

    /**
     * @brief Get the current primitive type.
     * @return PrimitiveType contained in the object
     */
    PrimitiveType primitiveType() const noexcept;

    /**
     * @brief Move all vertex array in this object into a given offset
     * @param offset Offset to move
     */
    void move(const htps::vector2df& offset) noexcept;

    /**
     * @brief Move all vertex array in this object into a given x
     * @param offset Offset x to move
     */
    void moveX(const htps::f32 xOffset) noexcept;

    /**
     * @brief Move all vertex array in this object into a given y
     * @param offset Offset y to move
     */
    void moveY(const htps::f32 yOffset) noexcept;

private:
    BasicVertexArray m_vertices;
    PrimitiveType m_primitiveType{PrimitiveType::Triangles};
};
}  // namespace haf::scene

#endif
