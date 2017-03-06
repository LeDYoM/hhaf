#include "statescontroller.hpp"

namespace lib
{
	namespace gui
	{
		void StatesController::configure()
		{
			activeNodeIndex.setCallback([this]() 
			{
				nodes()[m_lastActiveNodeIndex]->visible = false;
				nodes()[activeNodeIndex()]->visible = true;
			});
		}
	}
}
