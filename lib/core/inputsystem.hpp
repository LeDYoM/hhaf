#pragma once

#ifndef LIB_INPUTSYSTEM_INCLUDE_HPP
#define LIB_INPUTSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/key.hpp>
#include "appservice.hpp"
#include <list>

namespace lib
{
    namespace core
    {
        class Host;
    }
	namespace scene
	{
		class InputComponent;
	}
	namespace input
	{
		class InputSystem final : public AppService
		{
		public:
            InputSystem(core::Host& host);
            using AppService::AppService;
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
