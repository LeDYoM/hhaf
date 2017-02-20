#include "inputreadercomponent.hpp"

#include <lib/core/log.hpp>
#include <algorithm>

namespace lib
{
	namespace draw
	{
		class InputComponent::InputComponentPrivate
		{
		public:
			InputComponentPrivate() {}
		};
		InputComponent::InputComponent()
			: m_private{ new InputComponentPrivate }
		{
		}

		InputComponent::~InputComponent()
		{
			__ASSERT(m_private, "Destructing private class that is nullptr");
			delete m_private;
			m_private _ nullptr;
		}

		void InputComponent::update()
		{
		}
	}
}
