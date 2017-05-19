#ifndef LIB_GUI_CHOOSECONTROL_LINE_INCLUDE_HPP__
#define LIB_GUI_CHOOSECONTROL_LINE_INCLUDE_HPP__

#pragma once

#include <lib/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/gui/optionmodel.hpp>

namespace lib
{
	namespace scene
	{
		class TTFont;
		namespace nodes
		{
			class NodeText;
			class DiscreteText;
		}
	}
	namespace gui
	{
		class ChooseControl;
		class ChooseControlLine : public scene::SceneNode
		{
		public:
			ChooseControlLine(SceneNode* parent, str name);
			ForwardProperty<std::string> text;
			ForwardProperty<string_vector> options;
			VirtualPropertyWrite<Rectf32> alignmentBox;
			VirtualPropertyWrite<sptr<scene::TTFont>> font;
			VirtualPropertyWrite<u32> characterSize;
			VirtualPropertyWrite<scene::Color> color;
			void create();
			void configure();
			const OptionModelIndex currentSelection() const noexcept;
		public:
			sptr<scene::nodes::NodeText> m_mainText;
			sptr<scene::nodes::DiscreteText> m_option;
		};
	}
}

#endif
