#include "choosecontrol.hpp"
#include "menumanager.hpp"
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/ianimation.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
#include <lib/draw/nodes/nodetext.hpp>

namespace lib
{
	namespace gui
	{
		using namespace draw;
		using namespace draw::nodes;

		ChooseControl::ChooseControl(MenuManager *parent, std::string name,
			std::function<void(const u32)> onSelected,
			const std::vector<sptr<OptionDescriptor>> labels)
			: SceneNode{ parent, std::move(name) }, m_onSelected{ onSelected }
		{
			const auto &cTheme(parent->currentTheme());
			descriptorCursorSize = cTheme.cursorDescriptor.m_size;
			m_cursorNode = createSceneNode("cursorNode");
			m_cursor = m_cursorNode->createRenderizable<NodeShape>("cursor", cTheme.cursorDescriptor.m_nVertex);
			m_cursor->box = { 1000, 100, descriptorCursorSize.x, descriptorCursorSize.y };
			m_cursor->color = cTheme.cursorDescriptor.m_color;
			m_cursor->configure();

			const bool menuType{ labels.empty()?false:labels[0]->_subOptionsLabels.empty() };

			const auto normalLabelAlign( menuType ? NodeText::AlignmentX::Center : NodeText::AlignmentX::Left );
			u32 count{};
			vector2df currentPos{};
			for (const auto& label : labels)
			{
				auto menuLine = createSceneNode("menuLineText" + std::to_string(count));
				menuLine->position = currentPos;
				auto text = menuLine->createRenderizable<NodeText>("name" + std::to_string(count));
				text->text = label->_text;
				text->font = cTheme.font;
				text->characterSize = cTheme.chSize;
				text->color = cTheme.textColor;
				text->alignmentBox = scenePerspective();
				text->alignmentX = normalLabelAlign;
				text->alignmentY = NodeText::AlignmentY::Top;
				text->configure();

				sptr<NodeText> subtext{ nullptr };
				if (!label->_subOptionsLabels.empty()) {
					subtext = menuLine->createRenderizable<NodeText>("sub_name" + std::to_string(count));
					subtext->text = label->_subOptionsLabels[label->_startValueIndex];
					subtext->font = cTheme.font;
					subtext->characterSize = cTheme.chSize;
					subtext->color = cTheme.textColor;
					subtext->alignmentBox = scenePerspective().resized({ -300,0 });
					subtext->alignmentX = NodeText::AlignmentX::Right;
					subtext->alignmentY = NodeText::AlignmentY::Top;
					subtext->configure();
				}

				currentPos.y += (cTheme.chSize + cTheme.incY);
				m_labelData.emplace_back(label->_subOptionsLabels,subtext,text, label->_startValueIndex);
				++count;
			}

			cursorSelectItem(0);
		}

		ChooseControl::~ChooseControl() = default;

		MenuManager * ChooseControl::menuManager() const
		{
			return dynamic_cast<MenuManager*>(parent());
		}

		u32 ChooseControl::selectedSubLabel(const u32 index) const
		{
			__ASSERT(index < m_labelData.size(), "Invalid index");
			return m_labelData[index].selectedSublabel;
		}

	
		void ChooseControl::updateSubLabelText(const u32 index)
		{
			m_labelData[index].subLabel->text = m_labelData[index].textSubLabel[m_labelData[index].selectedSublabel];
		}

		void ChooseControl::cursorSelectItem(const u32 nodeIndex)
		{
			__ASSERT(nodeIndex < m_labelData.size(), "Invalid select index for cursor");

			const auto &cTheme(menuManager()->currentTheme());

			m_labelData[_cursorItemSelected].label->color = cTheme.textColor;
			if (m_labelData[_cursorItemSelected].subLabel) {
				m_labelData[_cursorItemSelected].subLabel->color = cTheme.textColor;
			}

			_cursorItemSelected = nodeIndex;
			auto selectedText = m_labelData[nodeIndex].label;

			selectedText->color = cTheme.selectedTextColor;
			if (m_labelData[_cursorItemSelected].subLabel) {
				m_labelData[_cursorItemSelected].subLabel->color = cTheme.selectedTextColor;
			}

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
			auto index = m_labelData[_cursorItemSelected].selectedSublabel;

			if (m_labelData[_cursorItemSelected].textSubLabel.size() > 0) {
				if (index < 1) {
					index = m_labelData[_cursorItemSelected].textSubLabel.size()-1;
				} else {
					--index;
				}
				m_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
		}

		void ChooseControl::goRight()
		{
			auto index = m_labelData[_cursorItemSelected].selectedSublabel;

			if (m_labelData[_cursorItemSelected].textSubLabel.size() > 0) {
				if (index >= m_labelData[_cursorItemSelected].textSubLabel.size() - 1) {
					index = 0;
				} else {
					++index;
				}
				m_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
		}
	}
}
