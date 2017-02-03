#include "choosecontrol.hpp"
#include "menumanager.hpp"
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/ianimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>

namespace lib
{
	namespace menu
	{
		using namespace draw;

		ChooseControl::ChooseControl(const std::string &name, MenuManager *parent,
			std::function<void(const u32)> onSelected,
			const std::vector<sptr<OptionDescriptor>> labels)
			: RenderGroup{ name, parent }, m_onSelected{ onSelected }
		{
			const auto &cTheme(parent->currentTheme());
			descriptorCursorSize = cTheme.cursorDescriptor.m_size;
			m_cursor = createRenderizable<NodeShape>("cursor", descriptorCursorSize, nullptr, cTheme.cursorDescriptor.m_nVertex, cTheme.cursorDescriptor.m_color);

			const bool menuType{ labels.empty()?false:labels[0]->_subOptionsLabels.empty() };

			const auto normalLabelAlign( menuType ? NodeText::Alignment::Center : NodeText::Alignment::Left );
			u32 count{};
			vector2df currentPos{};
			for (const auto& label : labels)
			{
				auto text = createRenderizable<NodeText>("name" + std::to_string(count), label->_text, cTheme.font, cTheme.chSize, cTheme.textColor);
				text->setPositionWithAlignmentX(0, normalLabelAlign);
				text->position = { text->position().x, currentPos.y };

				sptr<NodeText> subtext{ nullptr };
				if (!label->_subOptionsLabels.empty()) {
					subtext = createRenderizable<NodeText>("sub_name" + count, label->_subOptionsLabels[label->_startValueIndex],cTheme.font,cTheme.chSize, cTheme.textColor);
					subtext->setPositionWithAlignment({ 1800,currentPos.y }, draw::NodeText::Alignment::Right);
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
			m_labelData[index].subLabel->text.set(m_labelData[index].textSubLabel[m_labelData[index].selectedSublabel]);
			m_labelData[index].subLabel->setPositionWithAlignmentX(1800.0f, NodeText::Alignment::Right);
		}

		void ChooseControl::cursorSelectItem(const u32 nodeIndex)
		{
			__ASSERT(nodeIndex < m_labelData.size(), "Invalid select index for cursor");

			const auto &cTheme(menuManager()->currentTheme());

			m_labelData[_cursorItemSelected].label->color.set(cTheme.textColor);
			if (m_labelData[_cursorItemSelected].subLabel) {
				m_labelData[_cursorItemSelected].subLabel->color.set(cTheme.textColor);
			}

			_cursorItemSelected = nodeIndex;
			auto selectedText = m_labelData[nodeIndex].label;

			selectedText->color.set(cTheme.selectedTextColor);
			if (m_labelData[_cursorItemSelected].subLabel) {
				m_labelData[_cursorItemSelected].subLabel->color.set(cTheme.selectedTextColor);
			}

			m_cursor->rotation.set(90);
			
			using namespace lib::draw;

			addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(120,m_cursor->position,
				m_cursor->position(), vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y },
				anim::noAction, anim::noAction));
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
