#ifndef LIB__INPUTSYSTEM_HPP__
#define LIB__INPUTSYSTEM_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace scene
	{
		class InputComponent;
	}
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
			const vector<Key> &pressedKeys() const noexcept;
			const vector<Key> &releasedKeys() const noexcept;
			const KeyStates &keyStates() const noexcept { return m_keyStates; }
			friend class lib::scene::InputComponent;
			KeyStates m_keyStates;
			vector<Key> m_pressedKeys;
			vector<Key> m_releasedKeys;
		};
	}
}

#endif
