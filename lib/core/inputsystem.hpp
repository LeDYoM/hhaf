#ifndef LIB__INPUTSYSTEM_HPP__
#define LIB__INPUTSYSTEM_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace core
	{
		class InputSystem final : public AppService
		{
		public:
			InputSystem();
			~InputSystem();
		private:
			input::KeyStates m_keyStates;
		};
	}
}

#endif
