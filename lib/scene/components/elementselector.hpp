#pragma once

#ifndef LIB_COMPONENT_ELEMENT_SELECTOR_INCLUDE_HPP__
#define LIB_COMPONENT_ELEMENT_SELECTOR_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/icomponent.hpp>

namespace lib
{
	namespace scene
	{
			class ElementSelector : public IComponent
			{
			public:
				ElementSelector();
				virtual ~ElementSelector();

/*				void goDown();
				void goUp();
				void goLeft();
				void goRight();

				Property<u32> selectedItem;

			private:
				const sptr<ChooseControlLine> currentLine() const;
				const sptr<ChooseControlLine> previouscurrentLine() const;
				void modelChanged();
				u32 previouslySelectedItem;

				vector_shared_pointers<ChooseControlLine> lines;
				*/
			};
	}
}

#endif
