#include "nodetext.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

namespace lib
{
	namespace draw
	{
		NodeText::NodeText(const std::string &name, const std::string& string, sptr<Font> font_, u32 characterSize_, const Color &color) :
			Renderizable{ name, nullptr, Triangles, 0, color }, 
			font{ font_, [this](auto) { updateGeometry(); } },
			text{ string, [this](auto) { updateGeometry(); } },
			characterSize{ characterSize_, [this](auto) { updateGeometry(); } },
			bounds{ Renderizable::bounds }
		{
			logConstruct("Name: ", name);

			updateGeometry();
		}

		NodeText::~NodeText()
		{
			logDestruct("Name: ", name());
		}

		void NodeText::updateGeometry()
		{
			Renderizable::bounds.set(m_vertices.generateText(font(), text(), characterSize(), m_isBold, m_isUnderlined, m_isStrikeThrough, m_isItalic));
			texture.set(msptr<Texture>(font()->getTexture(characterSize())));
			color.update();
		}

		void NodeText::setPositionWithAlignment(const vector2df &pos, Alignment alignment)
		{
			switch (alignment)
			{
			default:
			case Alignment::Left:
				position = pos;
				break;
			case Alignment::Center:
				position = { pos.x - (bounds().width / 2.0f), pos.y - (bounds().height / 2.0f) };
				break;
			case Alignment::Right:
				position = { pos.x - (bounds().width), pos.y - (bounds().height) };
				break;
			}
		}

		void NodeText::setPositionWithAlignmentX(const float x, Alignment alignment /*= Alignment::Left*/)
		{
			switch (alignment)
			{
			default:
			case Alignment::Left:
				position = { x, position().y };
				break;
			case Alignment::Center:
			{
				position = { x - (bounds().width / 2.0f), position().y };
			}
			break;
			case Alignment::Right:
				position = { x - (bounds().width), position().y };
				break;
			}
		}

		void NodeText::setPositionWithAlignmentY(const float y, Alignment alignment /*= Alignment::Left*/)
		{
			switch (alignment)
			{
			default:
			case Alignment::Left:
				position = { position().x, y };
				break;
			case Alignment::Center:
				position = { position().x, y - (bounds.get().height / 2.0f) };
				break;
			case Alignment::Right:
				position = { position().x, y - (bounds().height) };
				break;
			}
		}

		void NodeText::setAlignment(Alignment alignment)
		{
			setPositionWithAlignment(position(), alignment);
		}
	}
}
