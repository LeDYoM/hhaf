#include "vertexarray.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/scene/renderstatesstack.hpp>

namespace lib
{
	namespace scene
	{
		VertexArray::VertexArray(const PrimitiveType type, const u32 vertexCount) noexcept
			: m_vertices{ vertexCount }, m_primitiveType{ type } {}

		void VertexArray::draw() const
		{
			host().parentWindow().draw(*this, host().rStates().top());
		}

		void VertexArray::setColor(const Color &color)
		{
			if (!m_vertices.empty()) for (auto &v : m_vertices) v.color = color;
		}

		void VertexArray::move(const vector2df & offset) noexcept
		{
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) v.position += offset;
				m_bounds += offset;
			}
		}

		void VertexArray::moveX(const f32 xOffset) noexcept
		{
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) v.position.x += xOffset;
				m_bounds += vector2df{ xOffset, 0 };
			}
		}

		void VertexArray::moveY(const f32 yOffset) noexcept
		{
			if (!m_vertices.empty()) {
				for (auto &v : m_vertices) v.position.y += yOffset;
				m_bounds += vector2df{ 0, yOffset };
			}
		}
	}
}
