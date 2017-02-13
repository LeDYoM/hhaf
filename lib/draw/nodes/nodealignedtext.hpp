#ifndef _LIB_DRAW_NODEALIGNEDTEXT_HPP__
#define _LIB_DRAW_NODEALIGNEDTEXT_HPP__

#include <lib/draw/renderizable.hpp>
#include <lib/include/types.hpp>
#include "nodetext.hpp"

namespace lib
{
	namespace draw
	{
		class Font;
		class Texture;
		namespace nodes
		{
			class NodeAlignedText : public NodeText
			{
			public:
				enum class AlignmentX : u8
				{
					Left = 0,
					Center,
					Right
				};

				enum class AlignmentY : u8
				{
					Top = 0,
					Middle,
					Bottom
				};

				NodeAlignedText(str_const name, std::string txt, sptr<Font> font, u32 characterSize, const Color &color, Rectf32 alignBox, AlignmentX alignmentX, AlignmentY alignmentY);
				virtual ~NodeAlignedText();

				Property<std::string> text;
				Property<sptr<Font>> font;
				Property<u32> characterSize;
				Property<AlignmentX> alignmentX;
				Property<AlignmentY> alignmentY;
				Property<Rectf32> alignmentBox;

			private:
				void updateAlignmentX();
				void updateAlignmentY();
				void updateGeometry();
			};
		}
	}
}

#endif
