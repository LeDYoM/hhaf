#ifndef LIB_DRAW_VERTEXARRAY_HPP
#define LIB_DRAW_VERTEXARRAY_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>

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
			TriangleFan,
		};

		class VertexArray
		{
		public:
			VertexArray(const PrimitiveType type, const u32 vertexCount) noexcept;
			constexpr VertexArray(const VertexArray&) = default;
			VertexArray& operator=(const VertexArray&) = default;
			constexpr VertexArray(VertexArray&&) noexcept = default;
			VertexArray& operator=(VertexArray&&) noexcept = default;

			void draw() const;
			void setColor(const Color &color);
			inline bool empty() const noexcept { return m_vertices.empty(); }

			inline BasicVertexArray &verticesArray() noexcept { return m_vertices; }
			inline const BasicVertexArray &verticesArray() const noexcept { return m_vertices; }

			void setBounds(Rectf32 nBounds) noexcept { m_bounds = std::move(nBounds); }
			inline Rectf32 bounds() const noexcept{ return m_bounds; }
			inline PrimitiveType primitiveType() const noexcept { return m_primitiveType; }

			void move(const vector2df &offset) noexcept;
			void moveX(const f32 xOffset) noexcept;
			void moveY(const f32 yOffset) noexcept;
		private:

			BasicVertexArray m_vertices;
			Rectf32 m_bounds;
			PrimitiveType m_primitiveType;
		};
	}
}

#endif
