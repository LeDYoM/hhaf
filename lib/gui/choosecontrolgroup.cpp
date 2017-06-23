#include "choosecontrolgroup.hpp"
#include "choosecontrol.hpp"
#include "optionmodel.hpp"
#include <mtypes/include/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/scene/components/inputcomponent.hpp>

namespace lib
{
	namespace gui
	{
		ChooseControlGroup::ChooseControlGroup(scene::SceneNode *parent, str name, Theme theme)
			: scene::SceneNode{ parent, std::move(name) }, m_theme( theme ) { }

		void ChooseControlGroup::create()
		{
		}

		void ChooseControlGroup::configure()
		{
			auto inputComponent(ensureComponentOfType<scene::InputComponent>());
			inputComponent->setOnKeyPressedHandler([this](const lib::input::Key&key) {
				log_debug_info("Key pressed toChooseControlGroup");
				auto node(m_sController->activeNode()->snCast<ChooseControl>());
				if (key == input::Key::Down || key == input::Key::Numpad2) {
					node->goDown();
				}
				else if (key == input::Key::Up || key == input::Key::Numpad8) {
					node->goUp();
				}
				else if (key == input::Key::Left || key == input::Key::Numpad4) {
					node->goLeft();
				}
				else if (key == input::Key::Right || key == input::Key::Numpad8) {
					node->goRight();
				}
				else if (key == input::Key::Return || key == input::Key::Space) {
					log_debug_info("Calling onSelected with currentSelection(): ", currentSelection());
					OptionModelIndex currentSelected{ currentSelection() };
					__ASSERT(currentSelected.size() > 1, "currentSelected size must be > 1");
					OptionModelIndex predefinedPath{ options()[currentSelected[0]][currentSelected[1]].next };
					OptionModelIndex resultIndices(onSelected(OptionModelIndex(currentSelection())));
					log_debug_info("The onSelect returned ", resultIndices);
					if (resultIndices.empty()) {
						resultIndices = std::move(predefinedPath);
					}
					if (!resultIndices.empty()) {
						if (resultIndices[0] != m_sController->activeNodeIndex()) {
							m_sController->activeNodeIndex = resultIndices[0];
						}
						if (resultIndices.size() > 1) {
							m_sController->activeNode()->snCast<ChooseControl>()->selectedItem = resultIndices[1];
						}
					}
				}
			});

			box.setCallback([this]() {
				for_each_group([this](const sptr<SceneNode>&sceneNode) {
					if (auto chControl = sceneNode->snCast<ChooseControl>()) {
						chControl->box = box();
					}
				});
			});
			m_theme.font = host().resourceManager().getFont("game_menu.mainFont");
			m_theme.textColor = scene::colors::Blue;
			m_theme.selectedTextColor = scene::colors::Red;
			m_theme.chSize = 70;
			m_theme.incY = 1;
			m_theme.cursorDescriptor = CursorDescriptor{ 3, vector2df{ 90.0f, 90.0f },scene::colors::Red };
			u32 count{ 0 };

			for (const auto& option : options()) {
				auto chooseControl = createSceneNode<ChooseControl>("chooseControl"+str(count));
				chooseControl->box = box();
				chooseControl->optionModel = option;
//				chooseControl->configure();
				++count;
			}

			// Use an state controller to manager which node is active
			m_sController = muptr<StatesController>();
			// Set the nodes to it
			m_sController->nodes = &sceneNodes().nodes;
			// Set the index 0 as start node
			m_sController->activeNodeIndex = 0;
			// Set it ready to work
			m_sController->configure();

			// Set the user visible property able to modify the internal state
			currentControlIndex.setCallback([this]() { m_sController->activeNodeIndex = currentControlIndex(); });
		}

		ChooseControlGroup::~ChooseControlGroup() = default;

		const OptionModelIndex ChooseControlGroup::currentSelection() const noexcept
		{
			vector<u32> temp{ m_sController->activeNodeIndex() };
			vector<u32> controlSelection{m_sController->activeNode()->snCast<ChooseControl>()->currentSelection() };
			temp.reserve(temp.size() + controlSelection.size());
			temp.insert(std::move(controlSelection));
			return temp;
		}

		const Theme & ChooseControlGroup::currentTheme() const noexcept
		{
			return m_theme;
		}
	}
}
