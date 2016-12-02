#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <vector>
#include <lib/draw/vertex.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

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
			VertexArray();
			explicit VertexArray(const PrimitiveType type, const std::size_t vertexCount = 0);
			Vertex &operator [](const std::size_t index);
			const Vertex &operator [](const std::size_t index) const;
			void clear();
			void resize(const std::size_t vertexCount);
			void append(const sf::Vertex &vertex);
			void setPrimitiveType(const PrimitiveType type);
			PrimitiveType getPrimitiveType() const;
			Rectf32 getBounds() const;
			inline const BasicVertexArray *data() const { return &m_vertices; }
			inline const BasicVertexArray::size_type getVertexCount() const { return m_vertices.size(); }
		private:
			BasicVertexArray m_vertices;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
