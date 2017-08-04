#include "choosecontrolline.hpp"
#include "choosecontrol.hpp"

#include <lib/scene/ianimation.hpp>
#include <lib/scene/nodes/nodeshape.hpp>
#include <lib/scene/nodes/nodetext.hpp>
#include <lib/scene/nodes/discretetext.hpp>

namespace lib
{
	namespace gui
	{
		using namespace scene;
		using namespace scene::nodes;

		ChooseControlLine::ChooseControlLine(SceneNode* parent, str name)
			: SceneNode{parent,std::move(name)} {}

		void ChooseControlLine::create()
		{
			m_mainText = createRenderizable<NodeText>("m_mainText");
			m_option = createRenderizable<DiscreteText>("m_option");
		}

		void ChooseControlLine::setAlignmentBox(Rectf32 albox) noexcept
		{
			m_mainText->alignmentBox = albox; 
			if (m_option) m_option->alignmentBox = albox;
		}

		void ChooseControlLine::setFont(sptr<scene::TTFont> f) noexcept
		{
			m_mainText->font = f; 
			if (m_option) m_option->font = f;
		}

		void ChooseControlLine::setColor(const Color c) noexcept
		{
			m_mainText->color = c;
			if (m_option) m_option->color = c;
		}

		void ChooseControlLine::setCharacterSize(const u32 cs) noexcept
		{
			m_mainText->characterSize = cs; 
			if (m_option) m_option->characterSize = cs;
		}

		void ChooseControlLine::configure()
		{
			if (m_option->data().empty()) {
				m_option->visible = false;
				m_mainText->alignmentX = NodeText::AlignmentX::Center;
			}
			else {
				m_mainText->alignmentX = NodeText::AlignmentX::Left;
				m_option->alignmentX = NodeText::AlignmentX::Right;
			}

			m_mainText->configure();
			m_option->configure();
		}

		const OptionModelIndex ChooseControlLine::currentSelection() const noexcept
		{
			return m_option->data().empty() ? OptionModelIndex{} : OptionModelIndex{m_option->index()};
		}
	}
}
