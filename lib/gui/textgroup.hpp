#ifndef LIB_GUI_TEXT_GROUP_INCLUDE_HPP
#define LIB_GUI_TEXT_GROUP_INCLUDE_HPP

#pragma once

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <functional>

namespace lib
{
	namespace scene
	{
		class TTFont;
		namespace nodes
		{
			class NodeText;
		}
	}
	namespace gui
	{
		class TextGroup : public scene::SceneNode
		{
		public:
			TextGroup(SceneNode* parent, str name);
			Property<Rectf32> alignmentBox;
			Property<sptr<scene::TTFont>> font;
			Property<u32> characterSize;
			Property<scene::Color> color;
			void create();
			void configure();

			sptr<scene::nodes::NodeText> addTextLine(str text);
		private:
			void for_each_text(std::function<void(const sptr<scene::nodes::NodeText>&)> action) const;
			Rectf32 boxForNextLine() const;
			u32 numLines() const;
		};
	}
}

#endif
