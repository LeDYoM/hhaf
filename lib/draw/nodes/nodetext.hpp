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

				NodeText(str_const &&name);
				virtual ~NodeText();

				virtual void configure() override;

				Property<std::string> text;
				Property<sptr<Font>> font;
				Property<u32> characterSize;
				Property<AlignmentX> alignmentX;
				Property<AlignmentY> alignmentY;
				Property<Rectf32> alignmentBox;

			protected:
				void configureBase();
				void updateGeometry();
			private:
				void updateAlignmentX();
				void updateAlignmentY();
			};
		}
	}
}

#endif
