#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string & name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color & color_)
			: HasName{ name }, m_vertices{ type, vertexCount }, m_bounds{}, texture{ texture_ },
			bounds{ m_bounds },
			color{ color_,[this](const Color& nvalue) 
				{
					m_vertices.setColor(nvalue);
				}
			}
		{
			logConstruct("Name: ", name );
		}

		void Renderizable::updateFillColors()
		{
			m_vertices.setColor(color.get());
		}

		void Renderizable::draw()
		{
			if (m_visible) {
				auto handle = host().rStates().pushChanges(&getTransform(), texture.get().get());
				m_vertices.draw();
			}
		}
	}
}
