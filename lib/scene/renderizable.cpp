#include "renderizable.hpp"
#include <lib/core/host.hpp>
#include "scenemanager.hpp"
#include "renderdata.hpp"
#include "scenenode.hpp"

namespace lib
{
	namespace scene
	{
		void Renderizable::configure()
		{
			color.setCallback([this]() { m_vertices.setColor(color()); });
		}

		void Renderizable::render() const
		{
			if (visible() && !m_vertices.empty()) {
				host().parentWindow().draw({
					m_vertices,
					m_parent->globalTransform(),
					texture().get()
				});
			}
		}
	}
}
