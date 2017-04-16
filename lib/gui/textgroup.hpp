#ifndef LIB_GUI_TEXT_GROUP_INCLUDE_HPP
#define LIB_GUI_TEXT_GROUP_INCLUDE_HPP

#pragma once

#include <lib/include/types.hpp>
#include <lib/draw/scenenode.hpp>
#include <functional>

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
		class TextGroup : public draw::SceneNode
		{
		public:
			TextGroup(SceneNode* parent, str_const name);
			Property<Rectf32> alignmentBox;
			Property<sptr<draw::Font>> font;
			Property<u32> characterSize;
			Property<draw::Color> color;
			void create();
			void configure();

			sptr<draw::nodes::NodeText> addTextLine(str_const text);
		private:
			void for_each_text(std::function<void(const sptr<draw::nodes::NodeText>&)> action) const;
			Rectf32 boxForNextLine() const;
			u32 numLines() const;
		};
	}
}

#endif
