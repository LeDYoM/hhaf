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

			Rectf32 generateQuad(const vector2df &size);
			Rectf32 generateShape(const vector2df &size, const u32 granularity = 10);
			Rectf32 generateText(const sptr<Font> &, std::string str, const u32 characterSize,
				const bool bold, const bool underlined, const bool strikeThrough, const bool isItalic);

			void for_each_vertex(std::function<void(Vertex&)>&&);
			Rectf32 getBounds() const;

			void draw() const;
			void setColor(const Color color);
		private:
			BasicVertexArray m_vertices;
			PrimitiveType m_primitiveType;
			Property<Rectf32> bounds;
		};
	}
}

#endif
