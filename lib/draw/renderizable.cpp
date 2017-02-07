#include "renderizable.hpp"
#include "renderstates.hpp"
#include <lib/core/log.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(const std::string & name, sptr<Texture> texture_, PrimitiveType type, u32 vertexCount, const Color & color_)
			: core::HasName{ name }, m_vertices{ type, vertexCount }, texture{ std::move(texture_),{} },
			color{ color_,[this]() { m_vertices.setColor(color()); } },
			position{ {} ,[]() {} },
			rotation{ {} ,[]() {} }
		//	scale{ {} ,[]() {} } 
		{ }

		Renderizable::~Renderizable() = default;

		void Renderizable::draw()
		{
			if (name() == "backgroundTile_0_0")
			{
				int a = 0;
			}
			if (m_visible) {
				auto handle = host().rStates().pushChanges(nullptr, texture().get());
				m_vertices.draw();
			}
		}
	}
}
