#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include "renderizable.hpp"
#include "font.hpp"
#include "texture.hpp"

#include <string>
#include <vector>

namespace lib
{
	namespace draw
	{
		class NodeText : public Renderizable
		{
		public:
			enum class Alignment : u8
			{
				Left = 0,
				Center = 1,
				Right = 2
			};

			NodeText(const std::string &name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color);
			virtual ~NodeText();

			Property<std::string> text;
			Property<sptr<Font>> font;
			Property<u32> characterSize;

			void setPositionWithAlignment(const vector2df &pos, Alignment alignment);
			void setPositionWithAlignmentX(const float x, Alignment alignment = Alignment::Left);
			void setPositionWithAlignmentY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);
		private:
			void updateGeometry();
		};
	}
}

#endif
