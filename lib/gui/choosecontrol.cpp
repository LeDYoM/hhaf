#include "choosecontrol.hpp"
#include "menumanager.hpp"
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/draw/scene.hpp>
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

		ChooseControlLine::ChooseControlLine(draw::SceneNodeSPtr parent, str_const && name)
		{
			m_sceneNode = parent->createSceneNode(name);
			this->name.setGetter([this]() { return m_sceneNode->name(); });
		}

		void ChooseControlLine::create()
		{
			m_mainText = m_sceneNode->createRenderizable<NodeText>("m_mainText");
			m_option = m_sceneNode->createRenderizable<DiscreteText>("m_option");

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
				m_mainText->alignmentX = NodeText::AlignmentX::Center;
			}
			else {
				m_mainText->alignmentX = NodeText::AlignmentX::Left;
				m_option->alignmentX = NodeText::AlignmentX::Right;
			}

			m_mainText->configure();
			m_option->configure();
		}

		ChooseControl::ChooseControl(MenuManager *parent, str_const &&name,
			std::function<void(const u32)> onSelected,
			const std::vector<sptr<OptionDescriptor>> labels)
			: m_onSelected{ onSelected }
		{
			const auto &cTheme(parent->currentTheme());
			descriptorCursorSize = cTheme.cursorDescriptor.m_size;
			m_sceneNode = parent->createSceneNode(std::move(name));
			this->name.setGetter([this]() { return m_sceneNode->name(); });

			// Set the virtual al forwarded properties
			visible.setForwardProperty(&m_sceneNode->visible);
			m_cursorNode = m_sceneNode->createSceneNode("cursorNode");
			m_cursor = m_cursorNode->createRenderizable<NodeShape>("cursor", cTheme.cursorDescriptor.m_nVertex);
			m_cursor->box = { 1000, 100, descriptorCursorSize.x, descriptorCursorSize.y };
			m_cursor->color = cTheme.cursorDescriptor.m_color;
			m_cursor->configure();

			u32 count{};
			vector2df currentPos{};
			for (const auto& label : labels)
			{
				auto menuLine = msptr<ChooseControlLine>(m_sceneNode,"menuLineText" + std::to_string(count));
				menuLine->create();
				menuLine->text = label->_text;
				menuLine->font = cTheme.font;
				menuLine->characterSize = cTheme.chSize;
				menuLine->color = cTheme.textColor;
				menuLine->alignmentBox = m_sceneNode->scenePerspective().moved(currentPos);
				menuLine->options = label->_subOptionsLabels;
				menuLine->configure();

				currentPos.y += (cTheme.chSize + cTheme.incY);
				m_labelData.emplace_back(menuLine);
				++count;
			}

			cursorSelectItem(0);
		}

		ChooseControl::~ChooseControl() = default;

		MenuManager * ChooseControl::menuManager() const
		{
			return dynamic_cast<MenuManager*>(m_sceneNode->parent());
		}

		u32 ChooseControl::selectedSubLabel(const u32 index) const
		{
			__ASSERT(index < m_labelData.size(), "Invalid index");
			return m_labelData[index].node->m_option->index();
		}

	
		void ChooseControl::cursorSelectItem(const u32 nodeIndex)
		{
			__ASSERT(nodeIndex < m_labelData.size(), "Invalid select index for cursor");

			const auto &cTheme(menuManager()->currentTheme());

			m_labelData[_cursorItemSelected].node->color = cTheme.textColor;
			_cursorItemSelected = nodeIndex;
			m_labelData[_cursorItemSelected].node->color = cTheme.selectedTextColor;

//			m_cursorNode->rotation.set(90);
//			auto p(vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y });
//			addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(120, m_cursorNode->position,
//				m_cursorNode->position(), vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y },
//				anim::noAction, anim::noAction));
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (m_labelData.size() - 1)) {
				cursorSelectItem(_cursorItemSelected + 1);
			} else {
				cursorSelectItem(0);
			}
		}

		void ChooseControl::goUp()
		{
			if (_cursorItemSelected > 0) {
				cursorSelectItem(_cursorItemSelected - 1);
			} else {
				cursorSelectItem(m_labelData.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			m_labelData[_cursorItemSelected].node->m_option->decrementIndex();
		}

		void ChooseControl::goRight()
		{
			m_labelData[_cursorItemSelected].node->m_option->incrementIndex();
		}
	}
}
