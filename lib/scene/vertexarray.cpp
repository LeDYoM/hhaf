#include "vertexarray.hpp"

namespace lib
{
	namespace scene
	{
		void VertexArray::setColor(const Color &color)
		{
			if (!m_vertices.empty()) for (auto &v : m_vertices) v.color = color;
		}

		void VertexArray::move(const vector2df & offset) noexcept
		{
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) v.position += offset;
				bounds = bounds() + offset;
			}
		}

		void VertexArray::moveX(const f32 xOffset) noexcept
		{
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) v.position.x += xOffset;
				bounds = bounds() + vector2df{ xOffset, 0 };
			}
		}

		void VertexArray::moveY(const f32 yOffset) noexcept
		{
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) v.position.y += yOffset;
				bounds = bounds() + vector2df{ 0, yOffset };
			}
		}
	}
}
