#pragma once

#ifndef LIB_SCENE_NODE_LABELTEXT_INCLUDE_HPP__
#define LIB_SCENE_NODE_LABELTEXT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/color.hpp>
#include "optionmodel.hpp"

namespace lib
{
	namespace scene
	{
		class TTFont;
		namespace nodes
		{
			class NodeText;
			class DiscreteText;

			class LabelText : public scene::SceneNode
			{
			public:
				LabelText(SceneNode* parent, str name);
				void setAlignmentBox(Rectf32 albox) noexcept;
				void setFont(sptr<scene::TTFont> f) noexcept;
				void setColor(const Color c) noexcept;
				void setCharacterSize(const u32 cs) noexcept;

				inline sptr<scene::nodes::NodeText> mainText() noexcept { return m_mainText; }
				inline const sptr<scene::nodes::NodeText> mainText() const noexcept { return m_mainText; }

				inline sptr<scene::nodes::DiscreteText> option() noexcept { return m_option; }
				inline const sptr<scene::nodes::DiscreteText> option() const noexcept { return m_option; }

				void create();
				void configure();

				void setModel(const str &text, const vector<str> &options = {});
				const OptionModelIndex currentSelection() const noexcept;
				vector<u32> selection();
				void enableReceiveInput(const bool enable);
			public:
				sptr<NodeText> m_mainText;
				sptr<DiscreteText> m_option;
			};
		}
	}
}

#endif
