#include "choosecontrol.hpp"
#include "menumanager.hpp"
#include <lib/core/resource.hpp>
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
			_cursor = createShape("cursor");
			_cursor->setPointCount(cTheme.cursorDescriptor.m_nVertex);
			_cursor->setColor(cTheme.cursorDescriptor.m_color);
			_cursor->setSize(descriptorCursorSize);

			const bool menuType{ labels.empty()?false:labels[0]->_subOptionsLabels.empty() };

			draw::Alignment normalLabelAlign{ menuType ? draw::Alignment::Center : draw::Alignment::Left };
			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto label : labels)
			{
				const bool hasSubLabels{ !labels[count]->_subOptionsLabels.empty() };

				auto text = createText("name" + count);
				text->setFont(*(cTheme.font->getAsFont()));
				text->setCharacterSize(cTheme.chSize);
				text->setString(labels[count]->_text);
				text->setColor(cTheme.textColor);
				text->setPositionX(0, normalLabelAlign);
				text->setPositionY(currentPos.y);

				sptr<draw::NodeText> subtext{ nullptr };
				if (hasSubLabels)
				{
					subtext = createText("sub_name" + count);
					subtext->setFont(*(cTheme.font->getAsFont()));
					subtext->setCharacterSize(cTheme.chSize);
					subtext->setString(labels[count]->_subOptionsLabels[labels[count]->_startValueIndex]);
					subtext->setColor(cTheme.textColor);
					subtext->setPositionX(1800, lib::draw::Alignment::Right);
					subtext->setPositionY(currentPos.y);
				}

				currentPos.y += (cTheme.chSize + cTheme.incY);
				_labelData.push_back(LabelData(labels[count]->_subOptionsLabels,subtext,text, labels[count]->_startValueIndex));
				++count;
			}

			cursorSelectItem(0);
		}

		ChooseControl::~ChooseControl() = default;

		MenuManager * ChooseControl::menuManager() const
		{
			return dynamic_cast<MenuManager*>(parent());
		}

		lib::u32 ChooseControl::getSelectedSubLabel(u32 index) const
		{
			__ASSERT(index < _labelData.size(), "Invalid index");
			return _labelData[index].selectedSublabel;
		}

		void ChooseControl::setSelectedSubLabel(u32 index, u32 subIndex)
		{
			__ASSERT(index < _labelData.size(), "Invalid index");
			_labelData[index].selectedSublabel = subIndex;
			updateSubLabelText(index);
		}
		
		void ChooseControl::updateSubLabelText(const u32 index)
		{
			_labelData[index].subLabel->setString(_labelData[index].textSubLabel[_labelData[index].selectedSublabel]);
			_labelData[index].subLabel->setPositionX(1800.0f, lib::draw::Alignment::Right);
		}

		void ChooseControl::cursorSelectItem(u32 nodeIndex)
		{
			__ASSERT(nodeIndex < _labelData.size(), "Invalid select index for cursor");

			const auto &cTheme(menuManager()->currentTheme());

			_labelData[_cursorItemSelected].label->setColor(cTheme.textColor);
			if (_labelData[_cursorItemSelected].subLabel)
			{
				_labelData[_cursorItemSelected].subLabel->setColor(cTheme.textColor);
			}

			_cursorItemSelected = nodeIndex;
			auto selectedText = _labelData[nodeIndex].label;

			selectedText->setColor(cTheme.selectedTextColor);
			if (_labelData[_cursorItemSelected].subLabel)
			{
				_labelData[_cursorItemSelected].subLabel->setColor(cTheme.selectedTextColor);
			}

			_cursor->setRotation(90);
			
			addAnimation(draw::anim::PositionAnimation::create(120, _cursor, 
				vector2df{ selectedText->getPosition().x - descriptorCursorSize.x, selectedText->getPosition().y }));
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (_labelData.size() - 1))
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
				cursorSelectItem(_labelData.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			auto index = _labelData[_cursorItemSelected].selectedSublabel;

			if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index < 1)
				{
					index = _labelData[_cursorItemSelected].textSubLabel.size()-1;
				}
				else
				{
					--index;
				}
				_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
		}

		void ChooseControl::goRight()
		{
			auto index = _labelData[_cursorItemSelected].selectedSublabel;

			if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index >= _labelData[_cursorItemSelected].textSubLabel.size() - 1)
				{
					index = 0;
				}
				else
				{
					++index;
				}
				_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);

			}
		}
	}
}
