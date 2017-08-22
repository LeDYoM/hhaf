#include "renderizable.hpp"
#include "renderstatesstack.hpp"
#include <lib/core/host.hpp>
#include "scenemanager.hpp"
#include "renderdata.hpp"

namespace lib
{
	namespace scene
	{
		void Renderizable::configure()
		{
			color.setCallback([this]() { m_vertices.setColor(color()); });
		}

		void Renderizable::draw() const
		{
			if (visible() && !m_vertices.empty()) {
				host().parentWindow().draw({
					m_vertices,
					sceneManager().rStates().top().m_transform,
					texture().get()
				});
			}
		}
	}
}
