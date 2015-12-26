#include "choosecontrol.hpp"
#include "menudescriptors.hpp"
#include "../scn/resource.hpp"

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, sptr<scn::Resource> font, 
			u32 chSize,float incY,sptr<CursorDescriptor> cursorDescriptor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: IMenuControl{ name }
		{
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
				renderizable->setPositionX(descriptorCursorSize.x);
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
//			cursor_->setOrigin(descriptorCursorSize / 2.0f);
			cursor_->setPosition(vector2df{ 0.0f, selectedText->getPosition().y } + (descriptorCursorSize / 2.0f));
			cursor_->setRotation(90);

			_cursor->setPositionY(selectedText->getPosition().y);
		}

		void ChooseControl::goDown()
		{

		}

		void ChooseControl::goUp()
		{

		}

	}
}
