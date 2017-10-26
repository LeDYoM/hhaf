#include "menupage.hpp"
#include "menupageinputcomponent.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/discretetext.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/scene/ttfont.hpp>
#include <lib/include/key.hpp>
#include <mtypes/include/function.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;
	using namespace lib::core;

	MenuPage::MenuPage(SceneNode *parent, str name) : BaseClass{ parent, std::move(name) } {}

	MenuPage::~MenuPage() = default;

	constexpr u32 LineSize = 72;

	void MenuPage::create()
	{
		m_normalFont = resourceManager().getResource<TTFont>("menu.mainFont", "resources/oldct.ttf");

		auto input = ensureComponentOfType<MenuPageInputComponent>();
		input->Up.connect({ this, &MenuPage::goUp });
		input->Down.connect({ this, &MenuPage::goDown });
		input->Left.connect({ this, &MenuPage::goLeft });
		input->Right.connect({ this, &MenuPage::goRight });
		input->Selected.connect({ this, &MenuPage::goSelected });
	}

	void MenuPage::setMainLabels(const vector<str>& texts, const Rectf32 &textBox)
	{
		position = textBox.leftTop();
		sceneNodeSize = textBox.size();
		tableSize = { 1,texts.size() };
		size_type c{ 0 };
		for (const str&t : texts) {
			auto newOption = createNodeAt(vector2du32{ 0,c }, str("label" + c));
			++c;
			newOption->node()->font = m_normalFont;
			newOption->node()->characterSize = LineSize;
			newOption->node()->color = colors::Blue;
			newOption->node()->text = t;
		}
		setSelectedItem(0);
	}

	void MenuPage::setSelectedItem(const size_type index)
	{
		m_previouslySelectedItem = m_selectedItem;
		m_selectedItem = index;
		updateSelection();
	}

	void MenuPage::updateSelection()
	{
		setColorToLine(m_previouslySelectedItem, colors::Blue);
		setColorToLine(m_selectedItem, colors::Red);
	}

	void MenuPage::setColorToLine(const size_type index, const Color &color)
	{
		for_each_tableSceneNode_in_y(index, [&color](const size_type, const sptr<TextSceneNode> &node) {
			node->node()->color = color;
		});
	}

	void MenuPage::goDown()
	{
		m_previouslySelectedItem = m_selectedItem;
		if (m_selectedItem < (tableSize().y - 1)) {
			setSelectedItem(m_selectedItem + 1);
		}
		else {
			setSelectedItem(0);
		}
	}

	void MenuPage::goUp()
	{
		m_previouslySelectedItem = m_selectedItem;
		if (m_selectedItem > 0) {
			setSelectedItem(m_selectedItem - 1);
		}
		else {
			setSelectedItem(tableSize().y - 1);
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

	void MenuPage::goSelected()
	{
		Selection(m_selectedItem);
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
