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

		const OptionModelIndex ChooseControl::currentSelection() const noexcept
		{
			std::vector<u32> lineSelection{ lines[selectedItem()]->currentSelection() };
			std::vector<u32> temp{ selectedItem() };
			temp.reserve(temp.size() + lineSelection.size());
			if (!lineSelection.empty())
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

			currentLine()->color = cTheme.textColor;
			selectedItem = nodeIndex;
			currentLine()->color = cTheme.selectedTextColor;

//			m_cursorNode->rotation.set(90);
//			auto p(vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y });
//			addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(120, m_cursorNode->position,
//				m_cursorNode->position(), vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y },
//				anim::noAction, anim::noAction));
		}

		void ChooseControl::goDown()
		{
			if (selectedItem() < (lines.size() - 1)) {
				cursorSelectItem(selectedItem() + 1);
			} else {
				cursorSelectItem(0);
			}
		}

		void ChooseControl::goUp()
		{
			if (selectedItem() > 0) {
				cursorSelectItem(selectedItem() - 1);
			} else {
				cursorSelectItem(lines.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			currentLine()->m_option->decrementIndex();
		}

		void ChooseControl::goRight()
		{
			currentLine()->m_option->incrementIndex();
		}
		const sptr<ChooseControlLine> ChooseControl::currentLine() const
		{
			return lines[selectedItem()];
		}
	}
}
