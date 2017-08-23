#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	namespace scene
	{
		using BasicVertexArray = vector<Vertex>;

		enum PrimitiveType
		{
			Points,
			Lines,
			LineStrip,
			Triangles,
			TriangleStrip,
			TriangleFan
		};

		class VertexArray
		{
		public:
			constexpr VertexArray(const PrimitiveType type, const u32 vertexCount) noexcept
				: m_vertices{ vertexCount }, bounds{ {}, {} }, m_primitiveType{ type } {}

			constexpr VertexArray(const VertexArray&) = default;
			constexpr VertexArray& operator=(const VertexArray&) = default;
			constexpr VertexArray(VertexArray&&) = default;
			constexpr VertexArray& operator=(VertexArray&&) = default;

			void setColor(const Color &color);
			constexpr bool empty() const noexcept { return m_vertices.empty(); }

			constexpr BasicVertexArray &verticesArray() noexcept { return m_vertices; }
			constexpr const BasicVertexArray &verticesArray() const noexcept { return m_vertices; }

			constexpr PrimitiveType primitiveType() const noexcept { return m_primitiveType; }

			void move(const vector2df &offset) noexcept;
			void moveX(const f32 xOffset) noexcept;
			void moveY(const f32 yOffset) noexcept;

			Property<Rectf32> bounds;

		private:
			BasicVertexArray m_vertices;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
