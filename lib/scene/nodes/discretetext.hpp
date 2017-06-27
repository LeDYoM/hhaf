#ifndef LIB_GUI_DISCRETETEXT_INCLUDE_HPP__
#define LIB_GUI_DISCRETETEXT_INCLUDE_HPP__

#include <lib/scene/renderizable.hpp>
#include <mtypes/include/types.hpp>
#include <lib/scene/nodes/nodetext.hpp>

namespace lib
{
	namespace scene
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
				void incrementIndex() noexcept;
				void decrementIndex() noexcept;
			};
		}
	}
}

#endif
