#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/vertex.hpp>
#include <vector>
#include <functional>

namespace lib
{
	namespace draw
	{
		using BasicVertexArray = std::vector<Vertex>;

		enum PrimitiveType
		{
			Points,
			Lines,
			LineStrip,
			Triangles,
			TriangleStrip,
			TriangleFan,
		};
		enum class VertexGeometryType
		{
			Quad,
			Ellipse,
			Text
		};
		class VertexArray
		{
		public:
			constexpr VertexArray() noexcept;
			explicit VertexArray(const PrimitiveType type, const std::size_t vertexCount = 0) noexcept;
			constexpr VertexArray(const VertexArray&) = default;
			VertexArray& operator=(const VertexArray&) = default;
			constexpr VertexArray(VertexArray&&) noexcept = default;
			VertexArray& operator=(VertexArray&&) noexcept = default;

			Rectf32 generateQuad(const vector2df &size);
			Rectf32 generateShape(const vector2df &size, u32 granularity = 10);
			Rectf32 generateFont(const vector2df &size);

			inline Vertex &VertexArray::operator [](const std::size_t index) { return m_vertices[index]; }
			inline const Vertex &VertexArray::operator [](const std::size_t index) const { return m_vertices[index]; }

			inline void clear() { m_vertices.clear(); }
			inline void resize(std::size_t vertexCount) { m_vertices.resize(vertexCount); }

			void for_each_vertex(std::function<void(Vertex&)>&&);
			void append(Vertex &&vertex) { m_vertices.emplace_back(std::move(vertex)); }
			template <typename... Args> inline void append(Args&&... args) { m_vertices.emplace_back(std::forward<Args&&>(args)...); }
			inline void setPrimitiveType(const PrimitiveType type) { m_primitiveType = type; }
			inline PrimitiveType getPrimitiveType() const { return m_primitiveType; }
			inline const BasicVertexArray::size_type getVertexCount() const { return m_vertices.size(); }
			Rectf32 getBounds() const;

			void draw() const;
			void setColor(const Color color);
		private:
			BasicVertexArray m_vertices;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
