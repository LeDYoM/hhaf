#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string & name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color & color_)
			: SceneNode{ name }, m_vertices{ type, vertexCount }, texture{ texture_,{} },
			color{ color_,[this](const Color& nvalue) 
				{
					m_vertices.setColor(nvalue);
				}
			}
		{
		}

		Renderizable::~Renderizable() = default;

		void Renderizable::draw()
		{
			if (m_visible) {
				auto handle = host().rStates().pushChanges(&getTransform(), texture().get());
				m_vertices.draw();
			}
		}
	}
}
