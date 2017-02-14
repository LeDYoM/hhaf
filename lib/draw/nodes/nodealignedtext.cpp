#include "nodealignedtext.hpp"

#include <lib/draw/font.hpp>
#include <lib/draw/texture.hpp>

#include <cmath>

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			NodeAlignedText::NodeAlignedText(str_const name, std::string txt, sptr<Font> font_, u32 characterSize_, const Color &color, Rectf32 alignBox, AlignmentX alignmentX_, AlignmentY alignmentY_) :
				NodeText{ name, txt, font_, characterSize_, color }, 
				alignmentX{ alignmentX_,[this]() { updateGeometry(); } }, alignmentY{ alignmentY_,[this]() {updateGeometry(); } }, alignmentBox{ alignBox,[this]() {updateGeometry(); } }
			{
				logConstruct("Name: ", name);

				text.setCallback([this]() {updateGeometry(); });

				updateGeometry();
			}

			NodeAlignedText::~NodeAlignedText()
			{
				logDestruct("Name: ", name());
			}

			void NodeAlignedText::updateGeometry()
			{
				NodeText::updateGeometry();
				updateAlignmentX();
				updateAlignmentY();
			}

			void NodeAlignedText::updateAlignmentX()
			{
				// To be called only after text set
				switch (alignmentX())
				{
				default:
				case AlignmentX::Left:
					break;
				case AlignmentX::Center:
					m_vertices.moveX((alignmentBox().right() / 2.f) - (bounds().right() / 2));
					break;
				case AlignmentX::Right:
					m_vertices.moveX(alignmentBox().right() - bounds().right());
					break;
				}
			}

			void NodeAlignedText::updateAlignmentY()
			{
				// To be called only after text set
				switch (alignmentY())
				{
				default:
				case AlignmentY::Top:
					break;
				case AlignmentY::Middle:
					m_vertices.moveY((alignmentBox().bottom() / 2.f) - (bounds().bottom() / 2));
					break;
				case AlignmentY::Bottom:
					m_vertices.moveY(alignmentBox().bottom() - bounds().bottom());
					break;
				}
			}
		}
	}
}
