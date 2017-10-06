#include "menupage.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/nodes/labeltext.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/discretetext.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;
	using namespace lib::core;
	MenuPage::MenuPage(SceneNode *parent, str name) : SceneNode{ parent, std::move(name) } {}

	MenuPage::~MenuPage() = default;

	constexpr u32 LineSize = 64;
	constexpr u32 LineSeparation = 32;

	void MenuPage::addModelLabel(OptionType oType)
	{
		auto newOption = createSceneNode<LabelText>("label");
		newOption->setFont(m_normalFont);
		newOption->setCharacterSize(LineSize);
		newOption->setColor(colors::Blue);
		newOption->mainText()->text = oType.first;
		options.push_back(std::move(newOption));
	}

	void MenuPage::create()
	{
		box.setCallback([this]() {
			for_each_group_as<LabelText>([this](const sptr<LabelText>&node) {
				node->setAlignmentBox(box());
			});
		});
//				const auto &cTheme(dynamic_cast<ChooseControlGroup*>(parent())->currentTheme());
		m_normalFont = resourceManager().getResource<TTFont>("menu.mainFont", "resources/oldct.ttf");
	}

	void MenuPage::repositionControls()
	{
		f32 center{ 0 };
		f32 posY{ 0 };
		for_each_group_as<LabelText>([&posY](const auto &node) {
			node->position = vector2df{ 0, static_cast<f32>(posY) };
			posY += (node->font()-> + LineSeparation);
		});
	}

	void MenuPage::goDown()
	{
		if (m_selectedItem < (options.size() - 1)) {
			++m_selectedItem;
		}
		else {
			m_selectedItem = 0;
		}
	}

	void MenuPage::goUp()
	{
		if (m_selectedItem > 0) {
			--m_selectedItem;
		}
		else {
			m_selectedItem = options.size() - 1;
		}
	}

	void MenuPage::goLeft()
	{
//		currentLine()->m_option->decrementIndex();
	}

	void MenuPage::goRight()
	{
//		currentLine()->m_option->incrementIndex();
	}

	/*
	void MenuPage::modelChanged()
	{
		clearNodes();
		u32 count{};
		vector2df currentPos{};
//				const auto &cTheme(parent()->snCast<ChooseControlGroup>()->currentTheme());
		for (const auto& label : optionModel())
		{
			auto menuLine = createSceneNode<LabelText>("menuLineText" + str(count));
			menuLine->create();
			menuLine->mainText()->text = label.text;
//					menuLine->setFont(cTheme.font);
//					menuLine->setCharacterSize(cTheme.characterSize);
//					menuLine->setColor(cTheme.textColor);
			menuLine->setAlignmentBox(box().moved(currentPos));
			menuLine->option()->data = label.subOptionsLabels;
			menuLine->configure();

//					currentPos.y += (cTheme.characterSize + cTheme.lineHeight);
			lines.push_back(std::move(menuLine));
			++count;
		}

		previouslySelectedItem = 0;
		selectedItem.setCallback([this]() {
			if (!lines.empty()) {
				__ASSERT(previouslySelectedItem < lines.size(), "Invalid previously selected index for cursor");
				__ASSERT(selectedItem() < lines.size(), "Invalid select index for cursor");

//						const auto &cTheme(parent()->snCast<ChooseControlGroup>()->currentTheme());

//						previouscurrentLine()->setColor(cTheme.textColor);
//						currentLine()->setColor(cTheme.selectedTextColor);
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
