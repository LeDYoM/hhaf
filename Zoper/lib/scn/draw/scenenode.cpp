#include "scenenode.hpp"

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			SceneNode::SceneNode()
				: m_bounds{}, m_geometryNeedUpdate{ false }, m_vertices{ sf::Triangles } {}


			SceneNode::~SceneNode()
			{
			}
		}
	}
}
