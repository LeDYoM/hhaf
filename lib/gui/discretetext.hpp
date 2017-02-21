#ifndef LIB_GUI_DISCRETETEXT_INCLUDE_HPP__
#define LIB_GUI_DISCRETETEXT_INCLUDE_HPP__

#include <lib/draw/renderizable.hpp>
#include <lib/include/types.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/draw/scenenode.hpp>

namespace lib
{
	namespace gui
	{
		class DiscreteText
		{
		public:
			DiscreteText(const draw::SceneNodeSPtr &parent, str_const name);
			virtual ~DiscreteText();
		private:
			sptr<draw::nodes::NodeText> m_alignedTextNode;
		};
	}
}

#endif
