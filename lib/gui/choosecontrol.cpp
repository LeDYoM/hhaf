#include "choosecontrol.hpp"
#include "choosecontrolline.hpp"
#include "choosecontrolgroup.hpp"
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>
#include <lib/draw/scene.hpp>
#include <lib/draw/ianimation.hpp>
#include <lib/draw/nodes/nodeshape.hpp>
#include <lib/draw/nodes/nodetext.hpp>
#include <lib/draw/nodes/discretetext.hpp>

namespace lib
{
	namespace gui
	{
		using namespace draw;

		ChooseControl::ChooseControl(lib::draw::SceneNode *parent, str_const &&name)
			: SceneNode{ parent, std::move(name) }
		{
		}

		ChooseControl::~ChooseControl() = default;

		void ChooseControl::configure()
		{
			const auto &cTheme(dynamic_cast<ChooseControlGroup*>(parent())->currentTheme());
			descriptorCursorSize = cTheme.cursorDescriptor.m_size;

			// Set the virtual forwarded properties
			m_cursorNode = createSceneNode("cursorNode");
			m_cursor = m_cursorNode->createRenderizable<nodes::NodeShape>("cursor", cTheme.cursorDescriptor.m_nVertex);
			m_cursor->box = { 1000, 100, descriptorCursorSize.x, descriptorCursorSize.y };
			m_cursor->color = cTheme.cursorDescriptor.m_color;
			m_cursor->configure();

			u32 count{};
			vector2df currentPos{};
			for (const auto& label : options())
			{
				auto menuLine = createSceneNode<ChooseControlLine>("menuLineText");
				menuLine->create();
				menuLine->text = label->_text;
				menuLine->font = cTheme.font;
				menuLine->characterSize = cTheme.chSize;
				menuLine->color = cTheme.textColor;
				menuLine->alignmentBox = scenePerspective().moved(currentPos);
				menuLine->options = label->_subOptionsLabels;
				menuLine->configure();

				currentPos.y += (cTheme.chSize + cTheme.incY);
				m_labelData.emplace_back(menuLine);
				++count;
			}

			cursorSelectItem(0);
		}

		ChooseControlGroup * ChooseControl::chooseControlGroup() const
		{
			return dynamic_cast<ChooseControlGroup*>(parent());
		}

		u32 ChooseControl::selectedSubLabel(const u32 index) const
		{
			__ASSERT(index < m_labelData.size(), "Invalid index");
			return m_labelData[index].node->m_option->index();
		}

	
		void ChooseControl::cursorSelectItem(const u32 nodeIndex)
		{
			__ASSERT(nodeIndex < m_labelData.size(), "Invalid select index for cursor");

			const auto &cTheme(chooseControlGroup()->currentTheme());

			m_labelData[_cursorItemSelected].node->color = cTheme.textColor;
			_cursorItemSelected = nodeIndex;
			m_labelData[_cursorItemSelected].node->color = cTheme.selectedTextColor;

//			m_cursorNode->rotation.set(90);
//			auto p(vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y });
//			addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(120, m_cursorNode->position,
//				m_cursorNode->position(), vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y },
//				anim::noAction, anim::noAction));
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (m_labelData.size() - 1)) {
				cursorSelectItem(_cursorItemSelected + 1);
			} else {
				cursorSelectItem(0);
			}
		}

		void ChooseControl::goUp()
		{
			if (_cursorItemSelected > 0) {
				cursorSelectItem(_cursorItemSelected - 1);
			} else {
				cursorSelectItem(m_labelData.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			m_labelData[_cursorItemSelected].node->m_option->decrementIndex();
		}

		void ChooseControl::goRight()
		{
			m_labelData[_cursorItemSelected].node->m_option->incrementIndex();
		}
	}
}
