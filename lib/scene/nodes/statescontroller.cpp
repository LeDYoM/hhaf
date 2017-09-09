#include "statescontroller.hpp"

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			void StatesController::configure()
			{
				activeNodeIndex.setCallback([this]()
				{
					for (auto& node : *nodes()) {
						node->visible = false;
					}
					(*(nodes()))[activeNodeIndex()]->visible = true;
				});
			}
		}
	}
}
