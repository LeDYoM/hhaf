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
				auto menuLine = createSceneNode<ChooseControlLine>("menuLineText"+std::to_string(count));
				menuLine->create();
				menuLine->text = label.text;
				menuLine->font = cTheme.font;
				menuLine->characterSize = cTheme.chSize;
				menuLine->color = cTheme.textColor;
				menuLine->alignmentBox = scenePerspective().moved(currentPos);
				menuLine->options = label.subOptionsLabels;
				menuLine->configure();

				currentPos.y += (cTheme.chSize + cTheme.incY);
				lines.emplace_back(menuLine);
				++count;
			}

			cursorSelectItem(0);
		}

		ChooseControlGroup * ChooseControl::chooseControlGroup() const
		{
			return dynamic_cast<ChooseControlGroup*>(parent());
		}

		const std::vector<u32> ChooseControl::currentSelection() const noexcept
		{
			std::vector<u32> lineSelection{ lines[_cursorItemSelected]->currentSelection() };
			std::vector<u32> temp{_cursorItemSelected};
			temp.reserve(temp.size() + lineSelection.size());
			std::copy(temp.end(),lineSelection.begin(), lineSelection.end());
			return temp;
		}

		u32 ChooseControl::selectedSubLabel(const u32 index) const
		{
			__ASSERT(index < lines.size(), "Invalid index");
			return lines[index]->m_option->index();
		}

	
		void ChooseControl::cursorSelectItem(const u32 nodeIndex)
		{
			__ASSERT(nodeIndex < lines.size(), "Invalid select index for cursor");

			const auto &cTheme(chooseControlGroup()->currentTheme());

			lines[_cursorItemSelected]->color = cTheme.textColor;
			_cursorItemSelected = nodeIndex;
			lines[_cursorItemSelected]->color = cTheme.selectedTextColor;

//			m_cursorNode->rotation.set(90);
//			auto p(vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y });
//			addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(120, m_cursorNode->position,
//				m_cursorNode->position(), vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y },
//				anim::noAction, anim::noAction));
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (lines.size() - 1)) {
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
				cursorSelectItem(lines.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			lines[_cursorItemSelected]->m_option->decrementIndex();
		}

		void ChooseControl::goRight()
		{
			lines[_cursorItemSelected]->m_option->incrementIndex();
		}
	}
}
