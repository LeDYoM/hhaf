#include "menupage.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/nodes/labeltext.hpp>
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/discretetext.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	MenuPage::MenuPage(lib::scene::SceneNode *parent, str name) : SceneNode{ parent, std::move(name) } {}

	MenuPage::~MenuPage() = default;

	void MenuPage::addLabel(const str & title, const vector<str>& option)
	{
		auto *newOption = createSceneNode<LabelText>("label");
//		newOption 
//		options.push_back();
	}

	void MenuPage::create()
	{
		box.setCallback([this]() {
			for_each_node_as<LabelText>([this](const sptr<LabelText>&node) {
				node->setAlignmentBox(box());
			});
		});
//				const auto &cTheme(dynamic_cast<ChooseControlGroup*>(parent())->currentTheme());
	}

	void MenuPage::goDown()
	{
		if (m_selectedItem < (lines.size() - 1)) {
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
			m_selectedItem = lines.size() - 1;
		}
	}

	void MenuPage::goLeft()
	{
		currentLine()->m_option->decrementIndex();
	}

	void MenuPage::goRight()
	{
		currentLine()->m_option->incrementIndex();
	}

	void MenuPage::modelChanged()
	{
		clearNodes();
		/*
		// Disable cursor
		m_cursorNode = createSceneNode("cursorNode");
		m_cursor = m_cursorNode->createRenderizable<nodes::NodeShape>("cursor", cTheme.cursorDescriptor.m_nVertex);
		m_cursor->box = { 1000, 100, descriptorCursorSize.x, descriptorCursorSize.y };
		m_cursor->color = cTheme.cursorDescriptor.m_color;
		*/
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
}
