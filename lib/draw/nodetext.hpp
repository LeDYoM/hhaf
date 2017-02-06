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

			void setTextWithAlignment(std::string text, const Rectf32 &box, const Alignment alignment);
			void setAlignment(const Rectf32 &box, const Alignment alignment);


			/**
			* Sets the position of the text using a provided pair of x coordinates to fit into
			* @param [in] The new value of the text property
			* @param [in] The x of the bounds
			* @param [in] The size of the x of the bounds
			* @param [in] The alignment to use
			*/
			void setTextWithAlignmentX(std::string text, const f32 x, const f32 sizeX, const Alignment alignment);

			/**
			* Sets the position of the text using a provided pair of y coordinates to fit into
			* @param [in] The new value of the text property
			* @param [in] The y of the bounds
			* @param [in] The size of the y of the bounds
			* @param [in] The alignment to use
			*/
			void setTextWithAlignmentY(std::string text, const f32 y, const f32 sizeY, const Alignment alignment);

			/**
			* Sets the position of the text using a provided pair of x coordinates to fit into. It maintains the same text
			* @param [in] The new value of the text property
			* @param [in] The x of the bounds
			* @param [in] The size of the x of the bounds
			* @param [in] The alignment to use
			*/
			void setAlignmentX(const f32 x, const f32 sizeX, const Alignment alignment);

			/**
			* Sets the position of the text using a provided pair of y coordinates to fit into. It maintains the same text
			* @param [in] The new value of the text property
			* @param [in] The y of the bounds
			* @param [in] The size of the y of the bounds
			* @param [in] The alignment to use
			*/
			void setAlignmentY(const f32 y, const f32 sizeY, const Alignment alignment);


		private:
			void updateGeometry();
		};
	}
}

#endif
