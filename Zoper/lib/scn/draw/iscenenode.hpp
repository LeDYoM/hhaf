#ifndef __LIB_ISCENENODE_HPP__
#define __LIB_ISCENENODE_HPP__

#include "idrawable.hpp"
#include "../../core/hasname.hpp"
namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class ISceneNode : public IDrawable
			{
			public:

				ISceneNode() {}
				virtual ~ISceneNode() {}
			};
		}
	}
}

#endif
