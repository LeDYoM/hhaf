#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name, PrimitiveType type, u32 vertexCount, const Color &color)
			: HasName{ name }, m_vertices{ type, vertexCount }, m_bounds{}, m_texture{ nullptr }, m_color{ color }
		{
			logConstruct("Name: ", name );
		}

		void Renderizable::setColor(const Color &color)
		{
			if (color != m_color) {
				m_color = color;
				m_vertices.setColor(m_color);
			}
		}

		void Renderizable::updateFillColors()
		{
			m_vertices.setColor(m_color);
		}

		void Renderizable::draw()
		{
			if (m_visible) {
				auto handle = host().rStates().pushChanges(&getTransform(), m_texture.get());
				m_vertices.draw();
			}
		}
	}
}
