#include "choosecontrol.hpp"
#include "menudescriptors.hpp"
#include "../scn/resource.hpp"
#include "../scn/draw/anim/positionanimation.hpp"

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, sptr<scn::Resource> font, 
			const scn::draw::Alignment alignment,
			u32 chSize,float incY,
			std::function<void(const u32, ChooseControl &self)> onSelected,
			sptr<CursorDescriptor> cursorDescriptor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: IMenuControl{ name }
		{
			_onSelected = onSelected;
			descriptorCursorSize = cursorDescriptor->_size;
			_cursor = createShape("cursor");
			auto cursor_ = _cursor->getAsEllipseShape();
			cursor_->setPointCount(cursorDescriptor->_nVertex);
			cursor_->setFillColor(cursorDescriptor->_color);
			cursor_->setSize(descriptorCursorSize);

			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto label : labels)
			{
				auto renderizable = createText("name" + count);
				auto text = renderizable->getAsText();
				text->setFont(*(font->getAsFont()));
				text->setCharacterSize(chSize);
				text->setString(labels[count]->_text);
				text->setColor(labels[count]->_color);
				renderizable->setPositionX(0,alignment);
				renderizable->setPositionY(currentPos.y);

				sptr<scn::draw::Renderizable> subrenderizable{ nullptr };
				if (labels[count]->_subOptionsLabels.size()>0)
				{
					subrenderizable = createText("sub_name" + count);
					auto subtext = subrenderizable->getAsText();
					subtext->setFont(*(font->getAsFont()));
					subtext->setCharacterSize(chSize);
					subtext->setString(labels[count]->_subOptionsLabels[labels[count]->_startValueIndex]);
					subtext->setColor(labels[count]->_color);
					subrenderizable->setPositionX(1800, lib::scn::draw::Alignment::Right);
					subrenderizable->setPositionY(currentPos.y);
				}

				currentPos.y += (chSize + incY);
				_labelData.push_back(LabelData(labels[count]->_subOptionsLabels,subrenderizable,renderizable, labels[count]->_startValueIndex));
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

		}

		void ChooseControl::updateSubLabelText(const u32 index)
		{
			std::string str(_labelData[index].textSubLabel[_labelData[index].selectedSublabel]);
			_labelData[index].subLabel->getAsText()->setString(str);
		}

		void ChooseControl::cursorSelectItem(u32 nodeIndex)
		{
			__ASSERT(nodeIndex < _labelData.size(), "Invalid select index for cursor");

			_cursorItemSelected = nodeIndex;
			auto selected = _labelData[nodeIndex].label;
			auto selectedText = selected->getAsText();

			auto cursor_ = _cursor->getAsEllipseShape();
			cursor_->setRotation(90);
			
			addAnimation(scn::draw::anim::PositionAnimation::create(200, _cursor, 
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
