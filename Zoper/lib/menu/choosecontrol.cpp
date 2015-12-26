#include "choosecontrol.hpp"
#include "optiondescriptor.hpp"
#include "../scn/resource.hpp"

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, sptr<scn::Resource> font, sptr<scn::draw::Renderizable> cursor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: IMenuControl{ name }
		{
			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto label : labels)
			{
				auto renderizable = createText("name"+count);
				auto text = renderizable->getAsText();
				text->setFont(*(font->getAsFont()));
				text->setCharacterSize(labels[count]->getCharSize());
				text->setString(labels[count]->getText());
				text->setColor(labels[count]->getColor());
				text->setPosition(currentPos);
				currentPos += labels[count]->getInc();
				currentPos.y += labels[count]->getCharSize();
				++count;
			}
			addRenderizable(cursor);
			vector2df pos{ -1 * (cursor->getAsCircleShape()->getLocalBounds().width), 0 };
			cursor->getAsCircleShape()->setRadius(100);
			cursor->setPosition(pos);
		}


		ChooseControl::~ChooseControl()
		{
		}
	}
}
