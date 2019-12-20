#include "menupage.hpp"
#include "menupageinputcomponent.hpp"
#include "../loaders/mainmenuresources.hpp"

#include <lib/include/liblog.hpp>
#include <lib/scene/scene.hpp>
#include <lib/system/resourcemanager.hpp>
#include <lib/resources/ttfont.hpp>
#include <lib/include/resources/ifont.hpp>
#include <lib/include/key.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>

#include <mtypes/include/function.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;
using namespace lib::core;

MenuPage::MenuPage(SceneNode *parent, str name)
    : BaseClass{parent, std::move(name)} {}

MenuPage::~MenuPage() = default;

constexpr size_type columnForOptions = 3U;

void MenuPage::onCreated()
{
    BaseClass::onCreated();
    auto resources_viewer = dataWrapper<ResourceView>();

    m_normalFont = resources_viewer->getTTFont(MainMenuResources::MenuFontId)->font(72);
#ifdef TEST_BMP_FONT
    m_normalFont = resources_viewer->getBMPFont(MainMenuResources::TestFontId);
#endif
    m_normalColor = colors::Blue;
    m_selectedColor = colors::Red;

    auto input = addComponentOfType<MenuPageInputComponent>();
    input->Up.connect({this, &MenuPage::goUp});
    input->Down.connect({this, &MenuPage::goDown});
    input->Left.connect({this, &MenuPage::goLeft});
    input->Right.connect({this, &MenuPage::goRight});
    input->Selected.connect({this, &MenuPage::goSelected});
}

void MenuPage::configure(MenuPageMode pageMode, const string_vector &titles, const vector<string_vector> options)
{
    m_pageMode = pageMode;
    Rectf32 textBox{rectFromSize(scenePerspective().size()).setLeftTop({0, 750}).setSize({2000, 4 * 150})};
    position = textBox.leftTop();
    sceneNodeSize = textBox.size();

    size_type titleColumn{0};

    switch (m_pageMode)
    {
    case zoper::MenuPageMode::Selector:
        setTableSize({2, titles.size()});
        titleColumn = 1;
        break;
    case zoper::MenuPageMode::Optioner:
        setTableSize({4, titles.size()});
        titleColumn = 0;
        break;
    default:
        log_assert(false, "Invalid enum value");
        break;
    }

    log_assert(titles.size() >= options.size() || options.size() == 0, "Invalid number of options");
    log_assert(titles.size() > 0, "Titles cannot be empty");
    size_type counter{0};
    for (auto &&title : titles)
    {
        auto newOption(createNodeAt(vector2dst{titleColumn, counter}, make_str("label", counter)));
        standarizeText(newOption);
        newOption->text.set(title);

        if (options.size() > counter)
        {
            auto discreteTextLabel(createNodeAt(vector2dst{columnForOptions, counter}, make_str("option", counter)));
            standarizeText(discreteTextLabel);
            auto discreteTextComponent(discreteTextLabel->addComponentOfType<DiscreteTextComponent>());
            discreteTextComponent->data.set(options[counter]);
        }

        ++counter;
    }
    setSelectedItem(0);
}

size_type MenuPage::SelectedOptionAtRow(const size_type row) const
{
    log_assert(row < tableSize().y, "Invalid row index parameter");
    auto node(nodeAt({columnForOptions, row}));
    if (auto discreteText = node->componentOfType<DiscreteTextComponent>())
    {
        return discreteText->index();
    }
    else
    {
        DisplayLog::error("The is no discrete text at ", vector2dst{columnForOptions, row});
    }
    return static_cast<size_type>(-1);
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
    for_each_tableSceneNode_in_y(index, [&color](const size_type, const sptr<BaseClass::ContainedElement> &node) {
        node->textColor.set(color);
    });
}

void MenuPage::standarizeText(const sptr<ContainedElement> &ntext)
{
    ntext->textColor.set(m_normalColor);
    ntext->font.set(m_normalFont);
}

void MenuPage::goDown()
{
    m_previouslySelectedItem = m_selectedItem;
    setSelectedItem((m_selectedItem < (tableSize().y - 1U)) ? (m_selectedItem + 1U) : (0U));
}

void MenuPage::goUp()
{
    m_previouslySelectedItem = m_selectedItem;
    setSelectedItem((m_selectedItem > 0U) ? (m_selectedItem - 1U) : (tableSize().y - 1U));
}

void MenuPage::goLeft()
{
    if (nodeHasOptions(m_selectedItem))
    {
        optionsLabelAt(m_selectedItem)->decrementIndex();
    }
}

void MenuPage::goRight()
{
    if (nodeHasOptions(m_selectedItem))
    {
        optionsLabelAt(m_selectedItem)->incrementIndex();
    }
}

void MenuPage::goSelected()
{
    Selection(m_selectedItem);
}

bool MenuPage::nodeHasOptions(const size_type y) const noexcept
{
    if (m_pageMode != MenuPageMode::Optioner)
    {
        return false;
    }

    if (auto node = nodeAt({columnForOptions, y}))
    {
        return node->componentOfType<DiscreteTextComponent>() != nullptr;
    }
    return false;
}

sptr<DiscreteTextComponent> MenuPage::optionsLabelAt(const size_type y)
{
    log_assert(m_pageMode == MenuPageMode::Optioner, "This page does not have options");
    auto node = nodeAt({columnForOptions, y});
    log_assert(node != nullptr, "This node does not have options");
    return node->componentOfType<DiscreteTextComponent>();
}
} // namespace zoper
