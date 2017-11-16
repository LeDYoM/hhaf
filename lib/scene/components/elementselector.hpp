#pragma once

#ifndef LIB_COMPONENT_ELEMENT_SELECTOR_INCLUDE_HPP__
#define LIB_COMPONENT_ELEMENT_SELECTOR_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib
{
	namespace scene
	{
			class ElementSelector : public IComponent
			{
			public:
				ElementSelector();
				virtual ~ElementSelector();


			};
	}
}

#endif
