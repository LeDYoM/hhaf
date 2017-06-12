#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <lib/scene/renderizable.hpp>
#include <mtypes/include/types.hpp>

namespace lib
{
	namespace scene
	{
		class TTFont;
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

				NodeText(str name);
				virtual ~NodeText();

				virtual void configure() override;

				Property<str> text;
				Property<sptr<TTFont>> font;
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
