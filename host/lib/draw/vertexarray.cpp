#include "vertexarray.hpp"
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		constexpr VertexArray::VertexArray() noexcept
			: m_vertices{}, m_primitiveType{ PrimitiveType::Points } {}


		VertexArray::VertexArray(const PrimitiveType type, const std::size_t vertexCount) noexcept
			: m_vertices{ vertexCount }, m_primitiveType{ type } {}

		Rectf32 VertexArray::generateQuad(const vector2df & size)
		{
			constexpr u32 nPoints = 4;
			constexpr u32 nVertex = nPoints + 2;

			m_vertices.resize(nVertex); // + 2 for center and repeated first point
			m_vertices[1].position = vector2df(0, 0);
			m_vertices[2].position = vector2df(size.x, 0);
			m_vertices[3].position = vector2df(size.x, size.y);
			m_vertices[4].position = vector2df(0, size.y);

			// Update the bounding rectangle
			m_vertices[5] = m_vertices[1]; // so that the result of getBounds() is correct
			Rectf32 bounds = getBounds();
			// Compute the center and make it the first vertex
			m_vertices[0].position.x = bounds.width / 2;
			m_vertices[0].position.y = bounds.height / 2;

			return bounds;

		}

		std::pair<BasicVertexArray::size_type, Rectf32> VertexArray::generateShape(VertexGeometryType, const vector2df & size, u32 granularity)
		{
			constexpr u32 nPoints = 4;
			constexpr u32 nVertex = nPoints + 2;

			m_vertices.resize(nVertex); // + 2 for center and repeated first point
			m_vertices[1].position = vector2df(0, 0);
			m_vertices[2].position = vector2df(size.x, 0);
			m_vertices[3].position = vector2df(size.x, size.y);
			m_vertices[4].position = vector2df(0, size.y);

			// Update the bounding rectangle
			m_vertices[5] = m_vertices[1]; // so that the result of getBounds() is correct
			Rectf32 bounds = getBounds();
			// Compute the center and make it the first vertex
			m_vertices[0].position.x = bounds.width / 2;
			m_vertices[0].position.y = bounds.height / 2;

			return{ m_vertices.size(), bounds };
		}

		Rectf32 VertexArray::generateFont(const vector2df & size)
		{
			return Rectf32();
		}

		void VertexArray::for_each_vertex(std::function<void(Vertex&)>&& f)
		{
			std::for_each(m_vertices.begin(), m_vertices.end(), std::move(f));
		}

		Rectf32 VertexArray::getBounds() const
		{
			if (!m_vertices.empty()) {
				f32 left = m_vertices[0].position.x;
				f32 top = m_vertices[0].position.y;
				f32 right = m_vertices[0].position.x;
				f32 bottom = m_vertices[0].position.y;

				for (const auto& v : m_vertices)
				{
					const vector2df &position{ v.position };

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
			else {
				return Rectf32{};
			}
		}

		void VertexArray::draw() const
		{
			host().parentWindow().draw((const sf::Vertex*)m_vertices.data(), m_vertices.size(), static_cast<sf::PrimitiveType>(m_primitiveType),
				host().rStates().internalStates());
		}

		void VertexArray::setColor(const Color color)
		{
			if (!m_vertices.empty()) for (auto &v : m_vertices) v.color = color;
		}
	}
}
