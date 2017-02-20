#ifndef LIB_COMPONENT_INPUT_INCLUDE_HPP__
#define LIB_COMPONENT_INPUT_INCLUDE_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/draw/icomponent.hpp>

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
		private:
			class InputComponentPrivate;
			InputComponentPrivate *m_private;
		};
	}
}

#endif
