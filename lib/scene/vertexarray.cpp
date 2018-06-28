#include "vertexarray.hpp"

namespace lib::scene
{
	void VertexArray::move(const vector2df & offset) noexcept
	{
		if (!m_vertices.empty()) {
			for (auto &v : m_vertices) v.position += offset;
//            std::transform(m_vertices.begin(), m_vertices.end(),
//                           m_vertices.begin(),
//                           [&offset](const auto &v) { return v + offset;} );
		}
	}

	void VertexArray::moveX(const f32 xOffset) noexcept
	{
		if (!m_vertices.empty()) {
			for (auto &v : m_vertices) v.position.x += xOffset;
		}
	}

	void VertexArray::moveY(const f32 yOffset) noexcept
	{
		if (!m_vertices.empty()) {
			for (auto &v : m_vertices) v.position.y += yOffset;
		}
	}
}
