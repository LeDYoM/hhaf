#ifndef LIB_COMPONENT_INPUT_INCLUDE_HPP__
#define LIB_COMPONENT_INPUT_INCLUDE_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/draw/icomponent.hpp>
#include <lib/include/key.hpp>

namespace lib
{
	namespace draw
	{
		class InputComponent : public IComponent
		{
		public:
			InputComponent();
			~InputComponent();

			virtual void update() override;
			
			bool isPressed(const input::Key key);
		private:
			class InputComponentPrivate;
			InputComponentPrivate *m_private;
		};
	}
}

#endif
