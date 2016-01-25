#ifndef __LIB_SCENENODE_HPP__
#define __LIB_SCENENODE_HPP__

#include "idrawable.hpp"
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
			};
		}
	}
}

#endif
