#ifndef __LIB_SCENENODE_HPP__
#define __LIB_SCENENODE_HPP__

#include "idrawable.hpp"
#include "vertexarray.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class SceneNode : public IDrawable, public sf::Transformable
			{
			public:
				SceneNode();
				virtual ~SceneNode();

				virtual floatRect getLocalBounds() const = 0;
				virtual floatRect getGlobalBounds() const = 0;

				virtual void ensureGeometryUpdate() const = 0;

			protected:
				mutable floatRect m_bounds;
				mutable bool m_geometryNeedUpdate;
				mutable VertexArray m_vertices;
			};
		}
	}
}

#endif
