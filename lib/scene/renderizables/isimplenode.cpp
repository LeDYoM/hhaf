#include "isimplenode.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/texture.hpp>

namespace lib::scene::nodes
{
	ISimpleNode::ISimpleNode(SceneNode *const parent, const str &name, const u32 pointCount)
		: Renderizable{ parent, name, TriangleFan, pointCount + 2 } 
	{
	}
}
