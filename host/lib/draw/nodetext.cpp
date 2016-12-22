#include "nodetext.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

namespace lib
{
	namespace draw
	{
		NodeText::NodeText(const std::string &name, const std::string& string, sptr<Font> font, u32 characterSize, const Color &color) :
			Renderizable{ name, nullptr, Triangles, 0, color }, m_string(string), m_font{ font }, m_characterSize{ characterSize } 
		{
			updateGeometry();
		}

		void NodeText::setString(const std::string & string)
		{
			if (m_string != string)
			{
				m_string = string;
				updateGeometry();
			}
		}

		void NodeText::setFont(sptr<Font> font)
		{
			if (m_font != font) {
				m_font = font;
				updateGeometry();
			}
		}

		void NodeText::setCharacterSize(const u32 size)
		{
			if (m_characterSize != size) {
				m_characterSize = size;
				updateGeometry();
			}
		}

		void NodeText::updateGeometry()
		{
			protectedBounds.set(m_vertices.generateText(m_font, m_string, m_characterSize, m_isBold, m_isUnderlined, m_isStrikeThrough, m_isItalic));
			m_texture = msptr<Texture>(m_font->getTexture(m_characterSize));
			updateFillColors();
		}

		void NodeText::setPositionWithAlignment(const vector2df &pos, Alignment alignment)
		{
			switch (alignment)
			{
			default:
			case Alignment::Left:
				setPosition(pos);
				break;
			case Alignment::Center:
				setPosition({ pos.x - (bounds.get().width / 2.0f), pos.y - (bounds.get().height / 2.0f) });
				break;
			case Alignment::Right:
				setPosition({ pos.x - (bounds.get().width), pos.y - (bounds.get().height) });
				break;
			}
		}

		void NodeText::setPositionWithAlignmentX(const float x, Alignment alignment /*= Alignment::Left*/)
		{
			const vector2df position(getPosition());
			switch (alignment)
			{
			default:
			case Alignment::Left:
				setPosition(vector2df{ x, position.y });
				break;
			case Alignment::Center:
			{
				auto a = vector2df{ x - (bounds.get().width / 2.0f), position.y };
				setPosition({ x - (bounds.get().width / 2.0f), position.y });
			}
			break;
			case Alignment::Right:
				setPosition({ x - (bounds.get().width), position.y });
				break;
			}
		}

		void NodeText::setPositionWithAlignmentY(const float y, Alignment alignment /*= Alignment::Left*/)
		{
			const vector2df position(getPosition());
			switch (alignment)
			{
			default:
			case Alignment::Left:
				setPosition({ position.x, y });
				break;
			case Alignment::Center:
				setPosition({ position.x, y - (bounds.get().height / 2.0f) });
				break;
			case Alignment::Right:
				setPosition({ position.x, y - (bounds.get().height) });
				break;
			}
		}

		void NodeText::setAlignment(Alignment alignment)
		{
			setPositionWithAlignment(getPosition(), alignment);
		}

	}
}
