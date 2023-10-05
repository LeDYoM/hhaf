#include <menu_paged/include/menu_page.hpp>
#include <menu_paged/include/menu_paged.hpp>
#include <menu_paged/include/menu_paged_input_component.hpp>
#include <haf/include/component/component_container.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/input/key.hpp>
#include <haf/include/scene_components/discretetextcomponent.hpp>

#include <htypes/include/function.hpp>

using namespace htps;

namespace haf::scene
{
MenuPage::~MenuPage() = default;

void MenuPage::onCreated()
{
    BaseClass::onCreated();
    TableSize = {0U, 0U};

    auto input{getOrCreateComponent<MenuPageInputComponent>()};
    input->Up.connect({this, &MenuPage::goUp});
    input->Down.connect({this, &MenuPage::goDown});
    input->Left.connect({this, &MenuPage::goLeft});
    input->Right.connect({this, &MenuPage::goRight});
    input->Selected.connect({this, &MenuPage::goSelected});
}

constexpr size_type columnForOptions{4U};

void MenuPage::onAllTableElementsCreated(fmath::vector2dst const table_size)
{
    BaseClass::onAllTableElementsCreated(table_size);

    if (table_size.x != 0U && table_size.y != 0U)
    {
        auto const& options{menu_options()};
        auto const& page_options{menu_page_options()};

        LogAsserter::log_assert(!options.empty(), "options cannot be empty");
        size_type counter{0U};
        for (auto&& option : options)
        {
            size_type const title_column{(page_options.centered_empty_option &&
                                    option->option().options().empty())
                                       ? 2U
                                       : 0U};

            auto newOption{nodeAt(vector2dst{title_column, counter})};
            standarizeText(newOption);
            newOption->Text = option->title();

            if (!option->option().options().empty())
            {
                auto discreteTextLabel{
                    nodeAt(vector2dst{columnForOptions, counter})};
                standarizeText(discreteTextLabel);
                auto discreteTextComponent{
                    discreteTextLabel->getOrCreateComponent<DiscreteTextComponent>()};
                discreteTextComponent->data = option->option().options();
            }

            ++counter;
        }
        setSelectedItem(0U);

        Selection.connect(
            [this, options](const size_type index, const s32 /*selection*/) {
                LogAsserter::log_assert(index <= options.size(),
                                        "Logical error: Received invalid "
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
}

rptr<MenuPaged const> MenuPage::parentMenuPaged() const
{
    return parentAs<MenuPaged>();
}

sptr<res::IFont> MenuPage::normalFont() const
{
    return parentMenuPaged()->NormalTextFont();
}

Color MenuPage::normalColor() const
{
    return parentMenuPaged()->NormalColor();
}

Color MenuPage::selectedColor() const
{
    return parentMenuPaged()->SelectedColor();
}

size_type MenuPage::SelectedOptionAtRow(const size_type row) const
{
    if (row < TableSize().y)
    {
        auto node(nodeAt({columnForOptions, row}));
        if (auto discreteText = node->componentOfType<DiscreteTextComponent>())
        {
            return discreteText->index();
        }
        else
        {
            logger::DisplayLog::error("The is no discrete text at ",
                              vector2dst{columnForOptions, row});
        }
    }
    else
    {
        logger::DisplayLog::error("Invalid row index parameter");
    }
    return static_cast<size_type>(-1);
}

void MenuPage::update()
{
    BaseClass::update();
    if (menu_options.readResetHasChanged())
    {
        if (!menu_options().empty())
        {
            TableSize = {5U, menu_options().size()};
        }
    }
}

vector<s32> MenuPage::optionsSelected() const
{
    vector<s32> result(TableSize().y);

    for (size_type index{0U}; index < TableSize().y; ++index)
    {
        result.emplace_back(
            (nodeHasOptions(index))
                ? static_cast<s32>(optionsLabelAt(index)->index())
                : -1);
    }
    return result;
}

void MenuPage::setSelectedItem(const size_type index)
{
    previously_selected_item_ = selected_item_;
    selected_item_            = index;
    updateSelection();
}

void MenuPage::updateSelection()
{
    setColorToLine(previously_selected_item_, normalColor());
    setColorToLine(selected_item_, selectedColor());
}

void MenuPage::setColorToLine(const size_type index, const Color& color)
{
    for_each_tableSceneNode_in_y(
        index,
        [&color](const size_type,
                 const sptr<BaseClass::ContainedElement>& node) {
            node->TextColor = color;
        });
}

void MenuPage::standarizeText(const sptr<ContainedElement>& ntext)
{
    ntext->TextColor = normalColor();
    ntext->Font      = normalFont();
}

void MenuPage::goDown()
{
    previously_selected_item_ = selected_item_;
    setSelectedItem(
        (selected_item_ < (TableSize().y - 1U)) ? (selected_item_ + 1U) : (0U));
}

void MenuPage::goUp()
{
    previously_selected_item_ = selected_item_;
    setSelectedItem((selected_item_ > 0U) ? (selected_item_ - 1U)
                                          : (TableSize().y - 1U));
}

void MenuPage::goLeft()
{
    if (nodeHasOptions(selected_item_))
    {
        optionsLabelAt(selected_item_)->decrementIndex();
    }
}

void MenuPage::goRight()
{
    if (nodeHasOptions(selected_item_))
    {
        optionsLabelAt(selected_item_)->incrementIndex();
    }
}

void MenuPage::goSelected()
{
    s32 option_selected_in_node{-1};

    if (nodeHasOptions(selected_item_))
    {
        option_selected_in_node =
            static_cast<s32>(optionsLabelAt(selected_item_)->index());
    }

    Selection(selected_item_, option_selected_in_node);
}

sptr<DiscreteTextComponent> MenuPage::optionsLabelAt(const size_type y) const
{
    auto node = nodeAt({columnForOptions, y});
    LogAsserter::log_assert(node != nullptr, "This node does not have options");
    return node->componentOfType<DiscreteTextComponent>();
}

bool MenuPage::nodeHasOptions(const size_type y) const noexcept
{
    if (TableSize().x >= columnForOptions)
    {
        if (auto node = nodeAt({columnForOptions, y}))
        {
            return node->componentOfType<DiscreteTextComponent>() != nullptr;
        }
    }
    return false;
}

}  // namespace haf::scene
