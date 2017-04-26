#include "renderizable.hpp"
#include <lib/draw/renderstatesstack.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace draw
	{
		Renderizable::Renderizable(str &&name, PrimitiveType type, u32 vertexCount)
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
			if (visible()) {
				auto handle = host().rStates().pushChanges(nullptr, texture().get());
				m_vertices.draw();
			}
		}
	}
}
