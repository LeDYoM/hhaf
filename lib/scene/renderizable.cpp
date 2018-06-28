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
        }

        Renderizable::~Renderizable()
        {
        }

		void Renderizable::render()
		{
            if (visible()) {
                updateGeometry();

                if (!m_vertices.empty()) {

                    if (color.readResetHasChanged()) {
                        updateColor();
                    }

                    host().parentWindow().draw({
                        m_vertices,
                        m_parent->globalTransform(),
                        texture().get()
                    });
                }
            }
        }

        void Renderizable::setBounds(Rectf32 bounds)
        {
            m_bounds = std::move(bounds);
        }

        void Renderizable::updateColor()
        {
            const Color c{color()};
            if (!m_vertices.empty()) {
                for (auto& v : m_vertices.verticesArray()) {
                    v.color = c;
                }
            }
        }
	}
}
