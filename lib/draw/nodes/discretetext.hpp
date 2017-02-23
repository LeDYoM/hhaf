#ifndef LIB_GUI_DISCRETETEXT_INCLUDE_HPP__
#define LIB_GUI_DISCRETETEXT_INCLUDE_HPP__

#include <lib/draw/renderizable.hpp>
#include <lib/include/types.hpp>
#include <lib/draw/nodes/nodetext.hpp>

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			class DiscreteText : public NodeText
			{
			public:
				using NodeText::NodeText;
				virtual void configure() override;

				Property<u32> index;
				Property<string_vector> data;
			protected:
				void configureBase();
			};
		}
	}
}

#endif
