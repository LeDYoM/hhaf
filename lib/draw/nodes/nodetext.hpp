#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <lib/draw/renderizable.hpp>
#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		class Font;
		class Texture;
		namespace nodes
		{
			class NodeText : public Renderizable
			{
			public:
				NodeText(str_const name, std::string txt, sptr<Font> font, u32 characterSize, const Color &color);
				virtual ~NodeText();

				Property<std::string> text;
				Property<sptr<Font>> font;
				Property<u32> characterSize;
			protected:
				void updateGeometry();
			};
		}
	}
}

#endif
