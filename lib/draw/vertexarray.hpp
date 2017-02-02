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
		class Font;
		class VertexArray
		{
		public:
			VertexArray(const PrimitiveType type, const u32 vertexCount) noexcept;
			constexpr VertexArray(const VertexArray&) = default;
			VertexArray& operator=(const VertexArray&) = default;
			constexpr VertexArray(VertexArray&&) noexcept = default;
			VertexArray& operator=(VertexArray&&) noexcept = default;

			void for_each_vertex(std::function<void(Vertex&)>&&);
			Rectf32 calculateBounds() const;

			void draw() const;
			void setColor(const Color color);
			void updateTextureCoords(const Rects32 textureRect);

			inline BasicVertexArray &verticesArray() noexcept { return m_vertices; }
			inline const BasicVertexArray &verticesArray() const noexcept { return m_vertices; }

			void setBounds(Rectf32 nBounds) noexcept { m_bounds = std::move(nBounds); }
			void autoUpdateBounds();
			inline Rectf32 bounds() const noexcept{ return m_bounds; }
			inline PrimitiveType primitiveType() const noexcept { return m_primitiveType; }
		private:
			BasicVertexArray m_vertices;
			Rectf32 m_bounds;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
