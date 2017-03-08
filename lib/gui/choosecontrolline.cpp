#include "choosecontrolline.hpp"
#include "choosecontrol.hpp"

#include <lib/draw/ianimation.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/draw/nodes/discretetext.hpp>

namespace lib
{
	namespace gui
	{
		using namespace draw;
		using namespace draw::nodes;

		ChooseControlLine::ChooseControlLine(SceneNode* parent, str_const && name)
			: SceneNode{parent,std::move(name)} {}

		void ChooseControlLine::create()
		{
			m_mainText = createRenderizable<NodeText>("m_mainText");
			m_option = createRenderizable<DiscreteText>("m_option");

			text.setForwardProperty(&(m_mainText->text));
			alignmentBox.setSetter([this](const auto&abox) { m_mainText->alignmentBox = abox; if (m_option) m_option->alignmentBox = abox; });

			font.setSetter([this](auto&f) { m_mainText->font = f; if (m_option) m_option->font = f; });
			characterSize.setSetter([this](auto&cs) { m_mainText->characterSize = cs; if (m_option) m_option->characterSize = cs; });
			color.setSetter([this](auto&c) { m_mainText->color = c; if (m_option) m_option->color = c; });
			options.setForwardProperty(&(m_option->data));
		}

		void ChooseControlLine::configure()
		{
			if (options().empty()) {
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
		const std::vector<u32> ChooseControlLine::currentSelection() const noexcept
		{
			return options().empty() ? std::vector<u32>{} : std::vector<u32>{m_option->index()};
		}
	}
}
