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
			~InputComponent() override;

			void update() override;
			
			bool isPressed(const input::Key key);

			emitter<const input::Key&> KeyPressed;
			emitter<const input::Key&> KeyReleased;

			static inline bool isAscii(const input::Key key) noexcept {
				return key >= input::Key::A && key <= input::Key::Z;
			}

			char toAscii(const input::Key key) noexcept;

			bool isShiftPressed() const;
			virtual void keyPressed(const input::Key&) {}
			virtual void keyReleased(const input::Key&) {}
		private:
			class InputComponentPrivate;
            uptr<InputComponentPrivate> priv_;
		};
	}
}

#endif
