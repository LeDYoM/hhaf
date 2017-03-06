#include "choosecontrolgroup.hpp"
#include "choosecontrol.hpp"

#include <lib/core/log.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>

#include <lib/core/events/inputevent.hpp>

namespace lib
{
	namespace gui
	{
		ChooseControlGroup::ChooseControlGroup(draw::SceneNode *parent, str_const&& name, Theme theme)
			: draw::SceneNode{ parent, std::move(name) }, m_theme( theme )
		{
		}

		void ChooseControlGroup::create()
		{
			parentScene()->addSubscription(events::KeyPressedEvent::subscribe([this](const events::Event&ev) {
				logDebug("Key pressed toChooseControlGroup");
				const auto &kEvent{ dynamic_cast<const events::KeyPressedEvent&>(ev) };
				auto node(m_sController->activeNode()->snCast<ChooseControl>());
				if (kEvent.key == input::Key::Down || kEvent.key == input::Key::Numpad2) {
					node->goDown();
				}
				else if (kEvent.key == input::Key::Up || kEvent.key == input::Key::Numpad8) {
					node->goUp();
				}
				else if (kEvent.key == input::Key::Left || kEvent.key == input::Key::Numpad4) {
					node->goLeft();
				}
				else if (kEvent.key == input::Key::Right || kEvent.key == input::Key::Numpad8) {
					node->goRight();
				}
				else if (kEvent.key == input::Key::Return || kEvent.key == input::Key::Space) {
					if (node->m_onSelected) {
						node->m_onSelected(node->_cursorItemSelected);
					}
				}
			}));
		}

		void ChooseControlGroup::configure()
		{
			m_theme.font = host().resourceManager().getFont("game_menu.mainFont");
			m_theme.textColor = draw::colors::Blue;
			m_theme.selectedTextColor = draw::colors::Red;
			m_theme.chSize = 70;
			m_theme.incY = 1;
			m_theme.cursorDescriptor = CursorDescriptor{ 3, vector2df{ 90.0f, 90.0f },draw::colors::Red };
			u32 count{ 0 };

			vector_shared_pointers<SceneNode> nodes;
			nodes.reserve(options().size());

			for (const auto& option : options()) {
				auto chooseControl = createSceneNode<ChooseControl>("chooseControl"+std::to_string(count));
				chooseControl->options = option;
				chooseControl->onSelected = onSelected()[0]; // <- TO DO: Change it
				chooseControl->configure();
				nodes.push_back(std::move(chooseControl));
				++count;
			}

			__ASSERT(count > 0 && !nodes.empty(), "The choose control group must be created with at least one element");
			// Use an state controller to manager which node is active
			m_sController = muptr<StatesController>();
			// Set the nodes to it
			m_sController->nodes = std::move(nodes);
			// Set the index 0 as start node
			m_sController->activeNodeIndex = 0;
			// Set it ready to work
			m_sController->configure();

			// Set the user visible property able to modify the internal state
			currentControlIndex.setCallback([this]() { m_sController->activeNodeIndex = currentControlIndex(); });
		}

		ChooseControlGroup::~ChooseControlGroup() = default;

		/*
		void ChooseControlGroup::addChooseControls(const std::vector<sptr<ChooseControl>> &steps)
		{
			for (auto& menuStep : steps)
			{
				addChooseControl(menuStep);
			}
		}

		void ChooseControlGroup::addChooseControl(sptr<ChooseControl> step)
		{
//			addSceneNode(step);
			m_steps.push_back(step);
		}

		void ChooseControlGroup::start(sptr<ChooseControl> &firstStep)
		{
			__ASSERT(firstStep, "Cannot start in nullptr step");
			changeStep(firstStep);
		}

		void ChooseControlGroup::start(const std::string &firstStep)
		{
			changeStep(firstStep);
		}

		void ChooseControlGroup::changeStep(const std::string &step)
		{
			for (auto& nstep : m_steps) {
				if (nstep->name() == step) {
					changeStep(nstep);
					break;
				}
			}
		}

		void ChooseControlGroup::changeStep(sptr<ChooseControl> &step)
		{
			setActiveStep(step);
		}

		void ChooseControlGroup::setActiveStep(sptr<ChooseControl> &step)
		{
			m_activeMenuStep = step;

			for (const auto &_step : m_steps) {
				_step->visible = (_step == step);
			}
		}

		*/
		const Theme & ChooseControlGroup::currentTheme() const noexcept
		{
			return m_theme;
		}
	}
}
