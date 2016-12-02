#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/vertex.hpp>
#include <vector>

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
		class VertexArray
		{
		public:
			constexpr VertexArray();
			explicit VertexArray(const PrimitiveType type, const std::size_t vertexCount = 0);
			inline Vertex &VertexArray::operator [](const std::size_t index) { return m_vertices[index]; }
			inline const Vertex &VertexArray::operator [](const std::size_t index) const { return m_vertices[index]; }

			inline void clear() noexcept { m_vertices.clear(); }
			template <typename T> inline void resize(T&& vertexCount) { m_vertices.resize(std::forward<T>(vertexCount)); }

			void append(Vertex &&vertex) { m_vertices.emplace_back(std::move(vertex)); }
			template <typename... Args> inline void append(Args&&... args) { m_vertices.emplace_back(std::forward<Args>(args)...); }
			inline void setPrimitiveType(const PrimitiveType type) { m_primitiveType = type; }
			inline PrimitiveType getPrimitiveType() const { return m_primitiveType; }
			Rectf32 getBounds() const;

			inline const BasicVertexArray *data() const noexcept { return &m_vertices; }
			inline const BasicVertexArray::size_type getVertexCount() const { return m_vertices.size(); }
		private:
			BasicVertexArray m_vertices;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
