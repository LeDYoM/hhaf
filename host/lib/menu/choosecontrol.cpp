#include "choosecontrol.hpp"
#include "menudescriptors.hpp"
#include "menumanager.hpp"
#include <lib/core/resource.hpp>
#include <lib/core/eventmanager.hpp>
#include <lib/include/events/inputevent.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, MenuManager *parent, sptr<core::Resource> font,
			const sf::Color &textColor, const sf::Color &selectedTextColor,
			const scn::draw::Alignment alignment,
			u32 chSize,float incY,
			std::function<void(const u32, ChooseControl &self)> onSelected,
			sptr<CursorDescriptor> cursorDescriptor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: scn::draw::RenderGroup{ name, parent }, _textColor{ textColor }, _selectedTextColor{ selectedTextColor }, _onSelected{ onSelected }
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
			parentScene()->addSubscription(events::KeyPressedEvent::subscribe([this](const events::Event&ev) {
				LOG_DEBUG("Key pressed from Chose control ");
				const auto kEvent_temp{ dynamic_cast<const events::KeyPressedEvent*>(&ev) };
				if (!kEvent_temp)
				{
					LOG_DEBUG("Is not this type");
				}
				const auto &kEvent{ dynamic_cast<const events::KeyPressedEvent&>(ev) };
				if (kEvent.key == input::Key::Down || kEvent.key == input::Key::Numpad2) {
					goDown();
				}
				else if (kEvent.key == input::Key::Up || kEvent.key == input::Key::Numpad8) {
					goUp();
				}
				else if (kEvent.key == input::Key::Return || kEvent.key == input::Key::Space) {
					if (_onSelected) {
						_onSelected(_cursorItemSelected, *this);
					}
				}
			}));
		}

		ChooseControl::~ChooseControl()
		{
			_labelData.clear();
			_cursor = nullptr;
		}

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
