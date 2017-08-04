#ifndef LIB_GUI_CHOOSECONTROL_LINE_INCLUDE_HPP__
#define LIB_GUI_CHOOSECONTROL_LINE_INCLUDE_HPP__

#pragma once

#include <mtypes/include/types.hpp>
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
			void setAlignmentBox(Rectf32 albox) noexcept;
			void setFont(sptr<scene::TTFont> f) noexcept;
			void setColor(const scene::Color c) noexcept;
			void setCharacterSize(const u32 cs) noexcept;

			inline sptr<scene::nodes::NodeText> mainText() noexcept { return m_mainText; }
			inline const sptr<scene::nodes::NodeText> mainText() const noexcept { return m_mainText; }

			inline sptr<scene::nodes::DiscreteText> option() noexcept { return m_option; }
			inline const sptr<scene::nodes::DiscreteText> option() const noexcept { return m_option; }

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
