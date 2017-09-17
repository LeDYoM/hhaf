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
			m_textGroup = attachedNode()->createSceneNode<nodes::TextGroup>("textGroup");
			m_textGroup->addText("Text1");
			m_textGroup->addText("Text2");
		}

		void TextSelectorController::update()
		{
		}

		void TextSelectorController::addText(str text)
		{
			m_textGroup->addText(std::move(text));
		}

		void TextSelectorController::selectNext(const bool goBack)
		{
			++m_selected;
			if (m_selected >= static_cast<s32>(m_textGroup->numTexts())) {
				m_selected = goBack ? 0 : (m_textGroup->numTexts() - 1);
			}
		}
		void TextSelectorController::selectPrevious(const bool goLast)
		{
			--m_selected;
			if (m_selected < 0) {
				m_selected = goLast ? (m_textGroup->numTexts() - 1) : 0;
			}
		}
		void TextSelectorController::selectIndex(const s32 index)
		{
			m_selected = index;
		}
	}
}
