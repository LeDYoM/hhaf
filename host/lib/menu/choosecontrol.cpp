#include "choosecontrol.hpp"
#include "menumanager.hpp"
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, MenuManager *parent,
			std::function<void(const u32)> onSelected,
			const std::vector<sptr<OptionDescriptor>> labels)
			: draw::RenderGroup{ name, parent }, m_onSelected{ onSelected }
		{
			const auto &cTheme(parent->currentTheme());
			descriptorCursorSize = cTheme.cursorDescriptor.m_size;
			m_cursor = createShape("cursor", vector2df{}, cTheme.cursorDescriptor.m_nVertex);
			m_cursor->setColor(cTheme.cursorDescriptor.m_color);
			m_cursor->setSize(descriptorCursorSize);

			const bool menuType{ labels.empty()?false:labels[0]->_subOptionsLabels.empty() };

			const auto normalLabelAlign( menuType ? draw::NodeText::Alignment::Center : draw::NodeText::Alignment::Left );
			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto& label : labels)
			{
				const bool hasSubLabels{ !label->_subOptionsLabels.empty() };

				auto text = createText("name" + count, label->_text, cTheme.font, cTheme.chSize);
				text->setColor(cTheme.textColor);
				text->setPositionWithAlignmentX(0, normalLabelAlign);
				text->setPositionY(currentPos.y);

				sptr<draw::NodeText> subtext{ nullptr };
				if (hasSubLabels) {
					subtext = createText("sub_name" + count, label->_subOptionsLabels[label->_startValueIndex],cTheme.font,cTheme.chSize);
					subtext->setColor(cTheme.textColor);
					subtext->setPositionWithAlignmentX(1800, draw::NodeText::Alignment::Right);
					subtext->setPositionY(currentPos.y);
				}

				currentPos.y += (cTheme.chSize + cTheme.incY);
				m_labelData.push_back(LabelData(label->_subOptionsLabels,subtext,text, label->_startValueIndex));
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
			m_labelData[index].subLabel->setString(m_labelData[index].textSubLabel[m_labelData[index].selectedSublabel]);
			m_labelData[index].subLabel->setPositionWithAlignmentX(1800.0f, draw::NodeText::Alignment::Right);
		}

		void ChooseControl::cursorSelectItem(const u32 nodeIndex)
		{
			__ASSERT(nodeIndex < m_labelData.size(), "Invalid select index for cursor");

			const auto &cTheme(menuManager()->currentTheme());

			m_labelData[_cursorItemSelected].label->setColor(cTheme.textColor);
			if (m_labelData[_cursorItemSelected].subLabel) {
				m_labelData[_cursorItemSelected].subLabel->setColor(cTheme.textColor);
			}

			_cursorItemSelected = nodeIndex;
			auto selectedText = m_labelData[nodeIndex].label;

			selectedText->setColor(cTheme.selectedTextColor);
			if (m_labelData[_cursorItemSelected].subLabel) {
				m_labelData[_cursorItemSelected].subLabel->setColor(cTheme.selectedTextColor);
			}

			m_cursor->setRotation(90);
			
			addAnimation(draw::anim::PositionAnimation::create(120, m_cursor, 
				vector2df{ selectedText->getPosition().x - descriptorCursorSize.x, selectedText->getPosition().y }));
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (m_labelData.size() - 1))
			{
				cursorSelectItem(_cursorItemSelected + 1);
			}
			else
			{
				cursorSelectItem(0);
			}
		}

		void ChooseControl::goUp()
		{
			if (_cursorItemSelected > 0)
			{
				cursorSelectItem(_cursorItemSelected - 1);
			}
			else
			{
				cursorSelectItem(m_labelData.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			auto index = m_labelData[_cursorItemSelected].selectedSublabel;

			if (m_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index < 1)
				{
					index = m_labelData[_cursorItemSelected].textSubLabel.size()-1;
				}
				else
				{
					--index;
				}
				m_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
		}

		void ChooseControl::goRight()
		{
			auto index = m_labelData[_cursorItemSelected].selectedSublabel;

			if (m_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index >= m_labelData[_cursorItemSelected].textSubLabel.size() - 1)
				{
					index = 0;
				}
				else
				{
					++index;
				}
				m_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);

			}
		}
	}
}
