#ifndef LIB__INPUTSYSTEM_HPP__
#define LIB__INPUTSYSTEM_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace input
	{
		class InputSystem final : public AppService
		{
		public:
			InputSystem();
			~InputSystem();

			void keyPressed(const Key key);
			void keyReleased(const Key key);
			void preUpdate();
			void postUpdate();
		private:
			KeyStates m_keyStates;
			std::list<Key> m_pressedKeys;
			std::list<Key> m_releasedKeys;
		};
	}
}

#endif
