#ifndef LIB_GUI_CHOOSECONTROL_LINE_INCLUDE_HPP__
#define LIB_GUI_CHOOSECONTROL_LINE_INCLUDE_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/draw/scenenode.hpp>

namespace lib
{
	namespace draw
	{
		class Font;
		namespace nodes
		{
			class NodeText;
			class DiscreteText;
		}
	}
	namespace gui
	{
		class ChooseControl;
		class ChooseControlLine : public draw::SceneNode
		{
		public:
			ChooseControlLine(SceneNode* parent, str_const&&name);
			ForwardProperty<std::string> text;
			ForwardProperty<string_vector> options;
			VirtualPropertyRead<str_const> name;
			VirtualPropertyWrite<Rectf32> alignmentBox;
			VirtualPropertyWrite<sptr<draw::Font>> font;
			VirtualPropertyWrite<u32> characterSize;
			VirtualPropertyWrite<draw::Color> color;
			void create();
			void configure();
			const std::vector<u32> currentSelection() const noexcept;
		public:
			sptr<draw::nodes::NodeText> m_mainText;
			sptr<draw::nodes::DiscreteText> m_option;
		};
	}
}

#endif
