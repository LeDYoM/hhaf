#include "renderizable.hpp"
#include "renderstates.hpp"
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(str_const &&name, PrimitiveType type, u32 vertexCount)
			: core::HasName{ std::move(name) }, m_vertices{ type, vertexCount },
			color{}
		{ }

		Renderizable::~Renderizable() = default;

		void Renderizable::configureBase()
		{
			color.setCallback([this]() { m_vertices.setColor(color()); });
		}

		void Renderizable::draw()
		{
			if (m_visible) {
				auto handle = host().rStates().pushChanges(nullptr, texture().get());
				m_vertices.draw();
			}
		}
	}
}
