#include "textgroup.hpp"

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

		TextGroup::TextGroup(SceneNode* parent, str_const name)
			: SceneNode{parent,std::move(name)} {}

		void TextGroup::create()
		{
//			characterSize.setSetter([this](auto&cs) { m_mainText->characterSize = cs; if (m_option) m_option->characterSize = cs; });
//			color.setSetter([this](auto&c) { m_mainText->color = c; if (m_option) m_option->color = c; });
		}

		void TextGroup::configure()
		{
			font.setCallback([this]() {
				for_each_text([this](const sptr<NodeText>&node) {
					node->font = font();
				});
			});

			characterSize.setCallback([this]() {
				for_each_text([this](const sptr<NodeText>&node) {
					node->characterSize = characterSize();
				});
			});

			color.setCallback([this]() {
				for_each_text([this](const sptr<NodeText>&node) {
					node->color = color();
				});
			});


			/*
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
			*/
		}

		void TextGroup::addTextLine(str_const text)
		{
			auto ptext = createRenderizable<NodeText>(text);
			ptext->text = std::move(text);
			ptext->font = font;
			ptext->characterSize = characterSize;
			ptext->color = color;
			ptext->alignmentBox = alignmentBox();
			ptext->alignmentX = NodeText::AlignmentX::Left;
			ptext->alignmentY = NodeText::AlignmentY::Top;
			ptext->configure();
		}

		void TextGroup::for_each_text(std::function<void(const sptr<NodeText>&)> action)
		{
			for_each_node([&action](const sptr<Renderizable>&node) {
				if (auto tnode = std::dynamic_pointer_cast<NodeText>(node)) {
					action(tnode);
				}
			});
		}
	}
}
