#ifndef LIB__INPUTSYSTEM_HPP__
#define LIB__INPUTSYSTEM_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"

namespace lib
{
	namespace core
	{
		class InputSystem : public AppService
		{
		public:
			InputSystem();
			~InputSystem();

		};
	}
}

#endif
