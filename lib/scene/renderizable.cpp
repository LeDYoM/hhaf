#include "renderizable.hpp"
#include <lib/scene/renderstatesstack.hpp>
#include <lib/core/host.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib
{
	namespace scene
	{
		Renderizable::Renderizable(str &&name, PrimitiveType type, u32 vertexCount)
			: core::HasName{ std::move(name) }, m_vertices{ type, vertexCount }, color{}
		{ }

		Renderizable::~Renderizable() = default;

		void Renderizable::configure()
		{
			color.setCallback([this]() { m_vertices.setColor(color()); });
		}

		void Renderizable::draw()
		{
			if (visible()) {
				auto handle = sceneManager().rStates().pushChanges(nullptr, texture().get());
				m_vertices.draw();
			}
		}
	}
}
