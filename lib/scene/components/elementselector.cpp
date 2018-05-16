#include "elementselector.hpp"
#include <lib/scene/components/inputcomponent.hpp>
#include <lib/include/core/log.hpp>
#include <lib/scene/scene.hpp>

namespace lib
{
	namespace scene
	{
			ElementSelector::ElementSelector() {}

			ElementSelector::~ElementSelector() = default;

/*
			const OptionModelIndex ChooseControl::currentSelection() const noexcept
			{
				vector<u32> lineSelection{ lines[selectedItem()]->currentSelection() };
				vector<u32> temp{ selectedItem() };
				temp.reserve(temp.size() + lineSelection.size());
				if (!lineSelection.empty())
					temp.insert(std::move(lineSelection));
				return temp;
			}

			void ChooseControl::goDown()
			{
				if (selectedItem() < (lines.size() - 1)) {
					selectedItem = selectedItem() + 1;
				}
				else {
					selectedItem = 0;
				}
			}

			void ChooseControl::goUp()
			{
				if (selectedItem() > 0) {
					selectedItem = selectedItem() - 1;
				}
				else {
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
				u32 count{};
				vector2df currentPos{};
				const auto &cTheme(parent()->snCast<ChooseControlGroup>()->currentTheme());
				for (const auto& label : optionModel())
				{
					auto menuLine = createSceneNode<ChooseControlLine>("menuLineText" + str(count));
					menuLine->create();
					menuLine->mainText()->text = label.text;
					menuLine->setFont(cTheme.font);
					menuLine->setCharacterSize(cTheme.characterSize);
					menuLine->setColor(cTheme.textColor);
					menuLine->setAlignmentBox(box().moved(currentPos));
					menuLine->option()->data = label.subOptionsLabels;
					menuLine->configure();

					currentPos.y += (cTheme.characterSize + cTheme.lineHeight);
					lines.push_back(std::move(menuLine));
					++count;
				}

				previouslySelectedItem = 0;
				selectedItem.setCallback([this]() {
					if (!lines.empty()) {
						__ASSERT(previouslySelectedItem < lines.size(), "Invalid previously selected index for cursor");
						__ASSERT(selectedItem() < lines.size(), "Invalid select index for cursor");

						const auto &cTheme(parent()->snCast<ChooseControlGroup>()->currentTheme());

						previouscurrentLine()->setColor(cTheme.textColor);
						currentLine()->setColor(cTheme.selectedTextColor);
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
			*/
	}
}
