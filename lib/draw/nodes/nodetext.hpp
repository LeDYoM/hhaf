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
				enum class Alignment : u8
				{
					Left = 0,
					Center = 1,
					Right = 2,
				};

				NodeText(str_const name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color);
				virtual ~NodeText();

				Property<std::string> text;
				Property<sptr<Font>> font;
				Property<u32> characterSize;


				/**
				* Sets the position of the text using a provided pair of x coordinates to fit into
				* @param [in] The new value of the text property
				* @param [in] The bounding box to align to
				* @param [in] The alignment to use
				*/
				void setTextWithAlignmentX(std::string text, const Rectf32 &box, const Alignment alignment);

				/**
				* Sets the position of the text using a provided pair of y coordinates to fit into
				* @param [in] The new value of the text property
				* @param [in] The bounding box to align to
				* @param [in] The alignment to use
				*/
				void setTextWithAlignmentY(std::string text, const Rectf32 &box, const Alignment alignment);

				/**
				* Sets the position of the text using a provided pair of x coordinates to fit into. It maintains the same text
				* @param [in] The bounding box to align to
				* @param [in] The alignment to use
				*/
				void setAlignmentX(const Rectf32 &box, const Alignment alignment);

				/**
				* Sets the position of the text using a provided pair of y coordinates to fit into. It maintains the same text
				* @param [in] The bounding box to align to
				* @param [in] The alignment to use
				*/
				void setAlignmentY(const Rectf32 &box, const Alignment alignment);

			private:
				void updateAlignmentX(const f32 left, const f32 right, const Alignment alignment);
				void updateAlignmentY(const f32 top, const f32 bottom, const Alignment alignment);
				void updateGeometry();
			};
		}
	}
}

#endif
