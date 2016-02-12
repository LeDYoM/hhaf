#include "eventreceiver.hpp"
#include "../eventmanager.hpp"

namespace lib
{
	namespace core
	{
		namespace events
		{
			EventReceiver::EventReceiver(EventManager *const eventManager) : m_eventManager{ eventManager }
			{

			}

			EventReceiver::~EventReceiver()
			{

			}
		}
	}
}
