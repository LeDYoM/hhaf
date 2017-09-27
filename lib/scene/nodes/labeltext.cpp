#include "labeltext.hpp"

#include <lib/scene/ianimation.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/discretetext.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
		{
			LabelText::LabelText(SceneNode* parent, str name)
				: SceneNode{ parent,std::move(name) } {}

			void LabelText::create()
			{
				m_mainText = createRenderizable<NodeText>("m_mainText");
				m_option = createRenderizable<DiscreteText>("m_option");
			}

			void LabelText::setAlignmentBox(Rectf32 albox) noexcept
			{
				m_mainText->alignmentBox = albox;
				if (m_option) m_option->alignmentBox = albox;
			}

			void LabelText::setFont(sptr<scene::TTFont> f) noexcept
			{
				m_mainText->font = f;
				if (m_option) m_option->font = f;
			}

			void LabelText::setColor(const Color c) noexcept
			{
				m_mainText->color = c;
				if (m_option) m_option->color = c;
			}

			void LabelText::setCharacterSize(const u32 cs) noexcept
			{
				m_mainText->characterSize = cs;
				if (m_option) m_option->characterSize = cs;
			}

			void LabelText::configure()
			{
				if (m_option->data().empty()) {
					m_option->visible = false;
					m_mainText->alignmentX = AlignmentX::Center;
				}
				else {
					m_mainText->alignmentX = AlignmentX::Left;
					m_option->alignmentX = AlignmentX::Right;
				}
			}

			void LabelText::setModel(const str &text, const vector<str> &options)
			{
				m_mainText->text = text;
				m_mainText->alignmentX = options.empty() ? AlignmentX::Left : AlignmentX::Center;
				m_option->visible = !options.empty();
				m_option->alignmentX = AlignmentX::Right;
				m_option->data = options;
			}

			const OptionModelIndex LabelText::currentSelection() const noexcept
			{
				return m_option->data().empty() ? OptionModelIndex{} : OptionModelIndex{ m_option->index() };
			}

			vector<u32> LabelText::selection()
			{
				return m_option->data().empty() ? vector<u32>{} : vector<u32>{ m_option->index() };
			}

			void LabelText::enableReceiveInput(const bool enable)
			{
			}
		}
	}
}
