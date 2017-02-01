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

		template <typename T>
		constexpr T PIConstant = 3.14159265358979323846;
		template <typename T>
		constexpr T PID2Constant = 3.14159265358979323846 / static_cast<T>(2);

		Rectf32 VertexArray::generateShape(const vector2df & size, const u32 granularity)
		{
			const u32 nPoints(granularity);
			const u32 nVertex = nPoints + 2;

			m_vertices.resize(nVertex); // + 2 for center and repeated first point
			const vector2df radius{ size / 2.0f };
			const f64 baseAngle((2 * PIConstant<f64>) / granularity);
			for (std::size_t i = 0; i < nPoints; ++i)
			{
				const f64 angle = (i*baseAngle) - (PID2Constant<f64>);
				const vector2dd r{ std::cos(angle) * radius.x, std::sin(angle) * radius.y };
				m_vertices[i + 1].position = vector2df{ static_cast<f32>(radius.x + r.x), static_cast<f32>(radius.y + r.y) };
			}

			m_vertices[nPoints + 1].position = m_vertices[1].position;

			// Update the bounding rectangle
			m_vertices[0] = m_vertices[1]; // so that the result of getBounds() is correct
			const Rectf32 bounds = calculateBounds();
			// Compute the center and make it the first vertex
			m_vertices[0].position.x = bounds.width / 2;
			m_vertices[0].position.y = bounds.height / 2;

			return bounds;
		}

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
