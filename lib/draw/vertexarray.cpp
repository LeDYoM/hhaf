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

		void VertexArray::draw() const
		{
			host().parentWindow().draw(*this, host().rStates().internalStates());
		}

		void VertexArray::setColor(const Color &color)
		{
			if (!m_vertices.empty()) for (auto &v : m_vertices) v.color = color;
		}

		void VertexArray::move(const vector2df & offset)
		{
			if (!m_vertices.empty()) for (auto &v : m_vertices) v.position += offset;
		}
	}
}
