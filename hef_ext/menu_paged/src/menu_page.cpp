#include <menu_paged/include/menu_page.hpp>
#include <menu_paged/include/menu_paged.hpp>
#include <menu_paged/include/menu_paged_input_component.hpp>

#include <lib/include/liblog.hpp>
#include <lib/input/include/key.hpp>
#include <lib/scene_components/include/discretetextcomponent.hpp>

#include <mtypes/include/function.hpp>

using namespace mtps;

namespace lib::scene
{
MenuPage::~MenuPage() = default;

void MenuPage::onCreated()
{
    BaseClass::onCreated();

    auto input = addComponentOfType<MenuPageInputComponent>();
    input->Up.connect({this, &MenuPage::goUp});
    input->Down.connect({this, &MenuPage::goDown});
    input->Left.connect({this, &MenuPage::goLeft});
    input->Right.connect({this, &MenuPage::goRight});
    input->Selected.connect({this, &MenuPage::goSelected});
}

MenuPaged *MenuPage::parentMenuPaged()
{
    return parentAs<MenuPaged>();
}

const MenuPaged *MenuPage::parentMenuPaged() const
{
    return parentAs<MenuPaged>();
}

sptr<IFont> MenuPage::normalFont() const
{
    return parentMenuPaged()->normalTextFont();
}

Color MenuPage::normalColor() const
{
    return parentMenuPaged()->normalColor();
}

Color MenuPage::selectedColor() const
{
    return parentMenuPaged()->selectedColor();
}

constexpr mtps::size_type columnForOptions = 4U;

mtps::size_type MenuPage::SelectedOptionAtRow(const mtps::size_type row) const
{
    if (row < tableSize().y)
    {
        auto node(nodeAt({columnForOptions, row}));
        if (auto discreteText = node->componentOfType<DiscreteTextComponent>())
        {
            return discreteText->index();
        }
        else
        {
            DisplayLog::error("The is no discrete text at ", vector2dst{columnForOptions, row});
        }
    }
    else
    {
        DisplayLog::error("Invalid row index parameter");
    }
    return static_cast<mtps::size_type>(-1);
}

void MenuPage::configure(vector<sptr<MenuPagedOption>> options,
    PageOptions page_options)
{
    setTableSize({5U, options.size()});

    log_assert(options.size() > 0U, "options cannot be empty");
    mtps::size_type counter{0U};
    for (auto &&option : options)
    {
        mtps::size_type title_column{
            (page_options.centered_empty_option && option->option().options().empty())
                ? 2U : 0U};

        auto newOption(createNodeAt(vector2dst{title_column, counter}, make_str("label", counter)));
        standarizeText(newOption);
        newOption->text.set(option->title());

        if (!option->option().options().empty())
        {
            auto discreteTextLabel(createNodeAt(vector2dst{columnForOptions, counter}, make_str("option", counter)));
            standarizeText(discreteTextLabel);
            auto discreteTextComponent(discreteTextLabel->addComponentOfType<DiscreteTextComponent>());
            discreteTextComponent->data.set(option->option().options());
        }

        ++counter;
    }
    setSelectedItem(0U);

    Selection.connect([this, options](const mtps::size_type index, const mtps::s32 /*selection*/) {
        log_assert(index <= static_cast<mtps::s32>(options.size()), "Logical error: Received invalid "
                                                              "index in Selection");

        const auto option = options[index];
        if (option->onSelected() > MenuPagedOption::NoAction)
        {
            if (option->onSelected() == MenuPagedOption::GoBack)
            {
                Canceled(optionsSelected());
                Back();
            }
            else
            {
                Accepted(optionsSelected());
                Forward(option->onSelected());
            }
        }
    });
}

vector<mtps::s32> MenuPage::optionsSelected() const
{
    vector<mtps::s32> result(tableSize().y);

    for (mtps::size_type index = 0U; index < tableSize().y; ++index)
    {
        result.emplace_back((nodeHasOptions(index)) ? optionsLabelAt(index)->index()
                                                    : -1);
    }
    return result;
}

void MenuPage::setSelectedItem(const mtps::size_type index)
{
    m_previouslySelectedItem = m_selectedItem;
    m_selectedItem = index;
    updateSelection();
}

void MenuPage::updateSelection()
{
    setColorToLine(m_previouslySelectedItem, normalColor());
    setColorToLine(m_selectedItem, selectedColor());
}

void MenuPage::setColorToLine(const mtps::size_type index, const Color &color)
{
    for_each_tableSceneNode_in_y(index, [&color](const mtps::size_type,
        const sptr<BaseClass::ContainedElement> &node)
        {
            node->textColor.set(color);
        }
    );
}

void MenuPage::standarizeText(const mtps::sptr<ContainedElement> &ntext)
{
    ntext->textColor.set(normalColor());
    ntext->font.set(normalFont());
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
    mtps::s32 option_selected_in_node{-1};

    if (nodeHasOptions(m_selectedItem))
    {
        option_selected_in_node = static_cast<mtps::s32>(
            optionsLabelAt(m_selectedItem)->index());
    }

    Selection(m_selectedItem, option_selected_in_node);
}

sptr<DiscreteTextComponent> MenuPage::optionsLabelAt(const mtps::size_type y) const
{
    auto node = nodeAt({columnForOptions, y});
    log_assert(node != nullptr, "This node does not have options");
    return node->componentOfType<DiscreteTextComponent>();
}

bool MenuPage::nodeHasOptions(const mtps::size_type y) const noexcept
{
    if (tableSize().x >= columnForOptions)
    {
        if (auto node = nodeAt({columnForOptions, y}))
        {
            return node->componentOfType<DiscreteTextComponent>() != nullptr;
        }
    }
    return false;
}

} // namespace lib::scene
