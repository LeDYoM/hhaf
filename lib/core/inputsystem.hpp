#ifndef LIB__INPUTSYSTEM_HPP__
#define LIB__INPUTSYSTEM_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include <list>
#include <functional>

namespace lib
{
	namespace draw
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
			const std::vector<Key> &pressedKeys() const noexcept;
			const std::vector<Key> &releasedKeys() const noexcept;
			const KeyStates &keyStates() const noexcept { return m_keyStates; }
			friend class lib::draw::InputComponent;
			KeyStates m_keyStates;
			std::vector<Key> m_pressedKeys;
			std::vector<Key> m_releasedKeys;
		};
	}
}

#endif
