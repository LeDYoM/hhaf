#include "vertexarray.hpp"

#include "font.hpp"
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		VertexArray::VertexArray(const PrimitiveType type, const u32 vertexCount) noexcept
			: m_vertices{ vertexCount }, m_primitiveType{ type } {}


		void VertexArray::for_each_vertex(std::function<void(Vertex&)>&& f)
		{
			std::for_each(m_vertices.begin(), m_vertices.end(), std::move(f));
		}

		Rectf32 VertexArray::calculateBounds() const
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

		void VertexArray::updateTextureCoords(const Rects32 textureRect)
		{
			const Rectf32 bounds(bounds());
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) {
					const f32 xratio((v.position.x - bounds.left) / bounds.width);
					const f32 yratio((v.position.y - bounds.top) / bounds.height);
					v.texCoords.x = textureRect.left + (textureRect.width * xratio);
					v.texCoords.y = textureRect.top + (textureRect.height * yratio);
				}
			}
		}

		void VertexArray::autoUpdateBounds()
		{
			m_bounds = calculateBounds();
		}

	}
}
