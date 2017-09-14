#include "textselectorcontroller.hpp"
#include <lib/scene/nodes/textgroup.hpp>
#include <mtypes/include/log.hpp>

namespace lib
{
	namespace scene
	{
		TextSelectorController::TextSelectorController()
		{
		}

		TextSelectorController::~TextSelectorController()
		{
		}

		void TextSelectorController::onAttached()
		{
			m_textGroup = attachedNode<nodes::TextGroup>();
			assert_release_error(m_textGroup, "You need to attach a TextSelectorController to a TextGroup node");
			if (m_textGroup) {

			}
		}

		void TextSelectorController::update()
		{
		}

		void TextSelectorController::addText(str text)
		{

		}
	}
}
