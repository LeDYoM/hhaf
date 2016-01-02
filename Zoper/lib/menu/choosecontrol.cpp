#include "choosecontrol.hpp"
#include "menudescriptors.hpp"
#include "../scn/resource.hpp"
#include "../scn/draw/anim/positionanimation.hpp"

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, sptr<scn::Resource> font, 
			const scn::draw::Alignment aleignment,
			u32 chSize,float incY,
			std::function<void(const u32)> onSelected,
			sptr<CursorDescriptor> cursorDescriptor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: IMenuControl{ name }
		{
			_onSelected = onSelected;
			descriptorCursorSize = cursorDescriptor->getSize();
			_cursor = createShape("cursor");
			auto cursor_ = _cursor->getAsEllipseShape();
			cursor_->setPointCount(cursorDescriptor->getNVertex());
			cursor_->setFillColor(cursorDescriptor->getColor());
			cursor_->setSize(descriptorCursorSize);

			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto label : labels)
			{
				auto renderizable = createText("name" + count);
				auto text = renderizable->getAsText();
				text->setFont(*(font->getAsFont()));
				text->setCharacterSize(chSize);
				text->setString(labels[count]->getText());
				text->setColor(labels[count]->getColor());
				renderizable->setPositionX(0,lib::scn::draw::Alignment::Center);
				renderizable->setPositionY(currentPos.y);
				currentPos.y += (chSize + incY);
				++count;
				_labels.push_back(renderizable);
			}

			cursorSelectItem(0);
		}


		ChooseControl::~ChooseControl()
		{
			_labels.clear();
			_cursor = nullptr;
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
					_onSelected(_cursorItemSelected);
				}
			}
		}

		void ChooseControl::onKeyReleased(sf::Event::KeyEvent kEvent)
		{

		}

		void ChooseControl::cursorSelectItem(u32 nodeIndex)
		{
			__ASSERT(nodeIndex < _labels.size(), "Invalid select index for cursor");

			_cursorItemSelected = nodeIndex;
			auto selected = _labels[nodeIndex];
			auto selectedText = selected->getAsText();

			auto cursor_ = _cursor->getAsEllipseShape();
			cursor_->setRotation(90);
			
			addAnimation(scn::draw::anim::PositionAnimation::create(200, _cursor, 
				vector2df{ selectedText->getPosition().x - descriptorCursorSize.x, selectedText->getPosition().y }));
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (_labels.size() - 1))
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
				cursorSelectItem(_labels.size()-1);
			}
		}

	}
}
