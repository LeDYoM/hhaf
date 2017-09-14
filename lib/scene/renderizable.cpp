#include "renderizable.hpp"
#include <lib/core/host.hpp>
#include "scenemanager.hpp"
#include "renderdata.hpp"
#include "scenenode.hpp"

namespace lib
{
	namespace scene
	{
		Renderizable::Renderizable(SceneNode * const parent, const str & name, const PrimitiveType type, const u32 vertexCount)
			: core::HasName{ name }, m_parent{ parent }, m_vertices{ type, vertexCount }
		{
			color.setCallback([this]() {
				if (!m_vertices.empty()) {
					for (auto& v : m_vertices.verticesArray()) {
						v.color = color();
					}
				}
			});
		}

		void Renderizable::render()
		{
			updateGeometry();
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
