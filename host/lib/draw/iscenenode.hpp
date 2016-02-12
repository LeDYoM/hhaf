#ifndef __LIB_ISCENENODE_HPP__
#define __LIB_ISCENENODE_HPP__

#include "idrawable.hpp"
#include <SFML/Graphics/Transformable.hpp>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class ISceneNode : public IDrawable, public sf::Transformable
			{
			public:
				ISceneNode();
				virtual ~ISceneNode();
			};
		}
	}
}

#endif
