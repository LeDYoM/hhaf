#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string &name, sptr<Texture> texture, PrimitiveType type, u32 vertexCount, const Color &color)
			: HasName{ name }, m_vertices{ type, vertexCount }, m_bounds{}, m_texture{ std::move(texture) }, m_color{ color },
			color{ m_color,[this]() 
			{
				m_vertices.setColor(m_color);
			}
		}
		{
			logConstruct("Name: ", name );
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
