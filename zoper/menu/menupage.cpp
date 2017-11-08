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
#include <lib/scene/components/discretetextcomponent.hpp>
#include <mtypes/include/function.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;
	using namespace lib::core;

	MenuPage::MenuPage(SceneNode *parent, str name) : BaseClass{ parent, std::move(name) } {}

	MenuPage::~MenuPage() = default;

	void MenuPage::create()
	{
		m_normalFont = resourceManager().getResource<TTFont>("menu.mainFont", "resources/oldct.ttf");
		m_normalColor = colors::Blue;
		m_selectedColor = colors::Red;
		m_normalCharacterSize = 72;

		auto input = ensureComponentOfType<MenuPageInputComponent>();
		input->Up.connect({ this, &MenuPage::goUp });
		input->Down.connect({ this, &MenuPage::goDown });
		input->Left.connect({ this, &MenuPage::goLeft });
		input->Right.connect({ this, &MenuPage::goRight });
		input->Selected.connect({ this, &MenuPage::goSelected });
	}

	void MenuPage::configure(MenuPageMode pageMode, const Rectf32 &textBox, 
		const string_vector &titles, const vector<string_vector> options)
	{
		m_pageMode = pageMode;
		position = textBox.leftTop();
		sceneNodeSize = textBox.size();

		size_type titleColumn{ 0 };

		switch (m_pageMode)
		{
		case zoper::MenuPageMode::Selector:
			tableSize = { 2, titles.size() };
			titleColumn = 1;
			break;
		case zoper::MenuPageMode::Optioner:
			tableSize = { 4, titles.size() };
			titleColumn = 0;
			break;
		default:
			assert_release(false, "Invalid enum value");
			break;
		}

		assert_debug(titles.size() >= options.size() || options.size() == 0, "Invalid number of options");
		assert_debug(titles.size() > 0, "Titles cannot be empty");
		size_type counter{ 0 };
		for (auto&& title : titles) {
			auto newOption(createNodeAt(vector2du32{ titleColumn,counter }, str("label" + counter)));
			standarizeText(newOption->node());
			newOption->node()->text = title;

			if (options.size() > counter) {
				auto discreteTextLabel(createNodeAt(vector2du32{ 3,counter }, str("option" + counter)));
				standarizeText(discreteTextLabel->node());
				auto discreteTextComponent = discreteTextLabel->ensureComponentOfType<DiscreteTextComponent>();
				discreteTextComponent->data.set(options[counter]);
			}

			++counter;
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

	void MenuPage::standarizeText(sptr<scene::nodes::NodeText> ntext)
	{
		ntext->color = m_normalColor;
		ntext->font = m_normalFont;
		ntext->characterSize = m_normalCharacterSize;
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
