#include "choosecontrol.hpp"
#include "choosecontrolline.hpp"
#include "choosecontrolgroup.hpp"
#include <lib/core/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/nodes/nodeshape.hpp>
#include <lib/scene/nodes/nodetext.hpp>
#include <lib/scene/nodes/discretetext.hpp>

namespace lib
{
	namespace gui
	{
		using namespace scene;

		ChooseControl::ChooseControl(lib::scene::SceneNode *parent, str name)
			: SceneNode{ parent, std::move(name) } {}

		ChooseControl::~ChooseControl() = default;

		void ChooseControl::create()
		{
			box.setCallback([this]() {
				for_each_node([this](const sptr<Renderizable>&node) {
					if (auto chControlLine = node->rnCast<ChooseControlLine>()) {
						chControlLine->alignmentBox = box();
					}
				});
			});
			const auto &cTheme(dynamic_cast<ChooseControlGroup*>(parent())->currentTheme());
			descriptorCursorSize = cTheme.cursorDescriptor.m_size;
			optionModel.setCallback([this]() {
				modelChanged();
			});
		}

		const OptionModelIndex ChooseControl::currentSelection() const noexcept
		{
			std::vector<u32> lineSelection{ lines[selectedItem()]->currentSelection() };
			std::vector<u32> temp{ selectedItem() };
			temp.reserve(temp.size() + lineSelection.size());
			if (!lineSelection.empty())
				temp.insert(temp.end(), lineSelection.begin(), lineSelection.end());
			return temp;
		}

		u32 ChooseControl::selectedSubLabel(const u32 index) const
		{
			__ASSERT(index < lines.size(), "Invalid index");
			return lines[index]->m_option->index();
		}

		void ChooseControl::goDown()
		{
			if (selectedItem() < (lines.size() - 1)) {
				selectedItem = selectedItem() + 1;
			} else {
				selectedItem = 0;
			}
		}

		void ChooseControl::goUp()
		{
			if (selectedItem() > 0) {
				selectedItem = selectedItem() - 1;
			} else {
				selectedItem = lines.size() - 1;
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

		const sptr<ChooseControlLine> ChooseControl::previouscurrentLine() const
		{
			return lines[previouslySelectedItem];
		}

		void ChooseControl::modelChanged()
		{
			clearNodes();
			/*
			// Disable cursor
			m_cursorNode = createSceneNode("cursorNode");
			m_cursor = m_cursorNode->createRenderizable<nodes::NodeShape>("cursor", cTheme.cursorDescriptor.m_nVertex);
			m_cursor->box = { 1000, 100, descriptorCursorSize.x, descriptorCursorSize.y };
			m_cursor->color = cTheme.cursorDescriptor.m_color;
			m_cursor->configure();
			*/
			u32 count{};
			vector2df currentPos{};
			const auto &cTheme(dynamic_cast<ChooseControlGroup*>(parent())->currentTheme());
			for (const auto& label : optionModel())
			{
				auto menuLine = createSceneNode<ChooseControlLine>("menuLineText" + std::to_string(count));
				menuLine->create();
				menuLine->text = label.text;
				menuLine->font = cTheme.font;
				menuLine->characterSize = cTheme.chSize;
				menuLine->color = cTheme.textColor;
				menuLine->alignmentBox = box().move(currentPos);
				menuLine->options = label.subOptionsLabels;
				menuLine->configure();

				currentPos.y += (cTheme.chSize + cTheme.incY);
				lines.emplace_back(menuLine);
				++count;
			}

			previouslySelectedItem = 0;
			selectedItem.setCallback([this]() {
				if (!lines.empty()) {
					__ASSERT(previouslySelectedItem < lines.size(), "Invalid previously selected index for cursor");
					__ASSERT(selectedItem() < lines.size(), "Invalid select index for cursor");

					const auto &cTheme(parent()->snCast<ChooseControlGroup>()->currentTheme());

					previouscurrentLine()->color = cTheme.textColor;
					currentLine()->color = cTheme.selectedTextColor;
					previouslySelectedItem = selectedItem();

					//			m_cursorNode->rotation.set(90);
					//			auto p(vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y });
					//			addAnimation(msptr<anim::IPropertyAnimation<vector2df>>(120, m_cursorNode->position,
					//				m_cursorNode->position(), vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y },
					//				anim::noAction, anim::noAction));
				}
			});
			selectedItem = 0;
		}
	}
}
