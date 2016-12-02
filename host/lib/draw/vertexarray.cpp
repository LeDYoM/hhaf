#include "vertexarray.hpp"
#include <lib/core/window.hpp>

namespace lib
{
	namespace draw
	{
		constexpr VertexArray::VertexArray() 
			: m_vertices{}, m_primitiveType{ PrimitiveType::Points } {}


		VertexArray::VertexArray(const PrimitiveType type, const std::size_t vertexCount)
			: m_vertices{ vertexCount }, m_primitiveType{ type } {}

		Rectf32 VertexArray::getBounds() const
		{
			if (!m_vertices.empty()) {
				f32 left = m_vertices[0].position.x;
				f32 top = m_vertices[0].position.y;
				f32 right = m_vertices[0].position.x;
				f32 bottom = m_vertices[0].position.y;

				for (const auto& v : m_vertices)
				{
					const vector2df &position = v.position;

					// Update left and right
					if (position.x < left)
						left = position.x;
					else if (position.x > right)
						right = position.x;

					// Update top and bottom
					if (position.y < top)
						top = position.y;
					else if (position.y > bottom)
						bottom = position.y;
				}

				return Rectf32{ left, top, right - left, bottom - top };
			}
			else
			{
				return Rectf32{};
			}
		}
	}
}
