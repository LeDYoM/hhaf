#include "choosecontrol.hpp"
#include "menudescriptors.hpp"
#include <lib/core/resource.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, sptr<core::Resource> font, 
			const sf::Color &textColor, const sf::Color &selectedTextColor,
			const scn::draw::Alignment alignment,
			u32 chSize,float incY,
			std::function<void(const u32, ChooseControl &self)> onSelected,
			sptr<CursorDescriptor> cursorDescriptor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: IMenuControl{ name }, _textColor{ textColor }, _selectedTextColor{ selectedTextColor }, _onSelected {onSelected}
		{
			descriptorCursorSize = cursorDescriptor->_size;
			_cursor = createShape("cursor");
			_cursor->setPointCount(cursorDescriptor->_nVertex);
			_cursor->setColor(cursorDescriptor->_color);
			_cursor->setSize(descriptorCursorSize);

			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto label : labels)
			{
				auto text = createText("name" + count);
				text->setFont(*(font->getAsFont()));
				text->setCharacterSize(chSize);
				text->setString(labels[count]->_text);
				text->setColor(textColor);
				text->setPositionX(0, alignment);
				text->setPositionY(currentPos.y);

				sptr<scn::draw::NodeText> subtext{ nullptr };
				if (labels[count]->_subOptionsLabels.size()>0)
				{
					subtext = createText("sub_name" + count);
					subtext->setFont(*(font->getAsFont()));
					subtext->setCharacterSize(chSize);
					subtext->setString(labels[count]->_subOptionsLabels[labels[count]->_startValueIndex]);
					subtext->setColor(textColor);
					subtext->setPositionX(1800, lib::scn::draw::Alignment::Right);
					subtext->setPositionY(currentPos.y);
				}

				currentPos.y += (chSize + incY);
				_labelData.push_back(LabelData(labels[count]->_subOptionsLabels,subtext,text, labels[count]->_startValueIndex));
				++count;
			}

			cursorSelectItem(0);
		}


		ChooseControl::~ChooseControl()
		{
			_labelData.clear();
			_cursor = nullptr;
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

		void ChooseControl::onKeyPressed(sf::Event::KeyEvent kEvent)
		{
			if (kEvent.code == sf::Keyboard::Down || kEvent.code == sf::Keyboard::Numpad2)
			{
				goDown();
			}
			else if (kEvent.code == sf::Keyboard::Up || kEvent.code == sf::Keyboard::Numpad8)
			{
				goUp();
			}
			else if (kEvent.code == sf::Keyboard::Return || kEvent.code == sf::Keyboard::Space)
			{
				if (_onSelected)
				{
					_onSelected(_cursorItemSelected,*this);
				}
			}
			else if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (kEvent.code == sf::Keyboard::Left || kEvent.code == sf::Keyboard::Numpad4)
				{
					goLeft();
				}
				else if (kEvent.code == sf::Keyboard::Right || kEvent.code == sf::Keyboard::Numpad6)
				{
					goRight();
				}
			}
		}

		void ChooseControl::onKeyReleased(sf::Event::KeyEvent kEvent)
		{
			kEvent;
		}

		void ChooseControl::updateSubLabelText(const u32 index)
		{
			_labelData[index].subLabel->setString(_labelData[index].textSubLabel[_labelData[index].selectedSublabel]);
			_labelData[index].subLabel->setPositionX(1800.0f, lib::scn::draw::Alignment::Right);
		}

		void ChooseControl::cursorSelectItem(u32 nodeIndex)
		{
			__ASSERT(nodeIndex < _labelData.size(), "Invalid select index for cursor");

			_labelData[_cursorItemSelected].label->setColor(_textColor);
			if (_labelData[_cursorItemSelected].subLabel)
			{
				_labelData[_cursorItemSelected].subLabel->setColor(_textColor);
			}

			_cursorItemSelected = nodeIndex;
			auto selectedText = _labelData[nodeIndex].label;

			selectedText->setColor(_selectedTextColor);
			if (_labelData[_cursorItemSelected].subLabel)
			{
				_labelData[_cursorItemSelected].subLabel->setColor(_selectedTextColor);
			}

			_cursor->setRotation(90);
			
			addAnimation(scn::draw::anim::PositionAnimation::create(120, _cursor, 
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
