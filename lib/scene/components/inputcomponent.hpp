#ifndef LIB_COMPONENT_INPUT_INCLUDE_HPP__
#define LIB_COMPONENT_INPUT_INCLUDE_HPP__

#pragma once

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/include/key.hpp>

namespace lib
{
	namespace scene
	{
		class InputComponent : public IComponent
		{
		public:
			InputComponent();
			~InputComponent();

			using KeyHandler_t = function<void(const input::Key&)>;

			void setOnKeyPressedHandler(KeyHandler_t keyHandlerPressed) noexcept;
			void setOnKeyReleasedHandler(KeyHandler_t keyHandlerReleased) noexcept;

			virtual void update() override;
			
			bool isPressed(const input::Key key);

			emitter<const input::Key&> KeyPressed;
			emitter<const input::Key&> KeyReleased;

			virtual void keyPressed(const input::Key&) {}
			virtual void keyReleased(const input::Key&) {}

		private:
			KeyHandler_t m_onKeyPressed{ nullptr };
			function<void(const input::Key&)> m_onKeyReleased{ nullptr };

			class InputComponentPrivate;
			InputComponentPrivate *m_private;
		};
	}
}

#endif
