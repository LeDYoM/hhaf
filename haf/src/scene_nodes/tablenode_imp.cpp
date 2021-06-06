#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <haf/include/scene_nodes/tablenode_imp.hpp>

namespace haf::scene::nodes
{

htps::vector2df TableNodeImp::cellSize() const
{
    return htps::vector2df{
        prop<SceneNodeSize>().get() /
        static_cast<htps::vector2df>(prop<TableSize>().get())};
}

void TableNodeImp::update()
{
    BaseClass::update();

    updateTableSizeIfNecessary();

    // Update row and column size
    if (prop<SceneNodeSize>().readResetHasChanged())
    {
        htps::vector2df const& cell_size{cellSize()};
        for_each_table_innerSceneNode(
            [this, cell_size](htps::vector2dst const& p, const htps::sptr<SceneNode>& n) {
                n->prop<Position>().set(cell_size * static_cast<htps::vector2df>(p));
            });
    }
}

void TableNodeImp::updateTableSizeIfNecessary()
{
    if (prop<TableSize>().readResetHasChanged())
    {
        setTableSize(prop<TableSize>().get());
        prop<SceneNodeSize>().setChanged();
    }
}

void TableNodeImp::setTableSize(htps::vector2dst const ntableSize)
{
    inner_nodes_.resize(ntableSize.x);

    for (auto& nodeColumn : inner_nodes_)
    {
        nodeColumn.resize(ntableSize.y);
    }
}

void TableNodeImp::setInnerSceneNodeAt(htps::vector2dst const index,
                                       htps::sptr<SceneNode> scene_node)
{
    LogAsserter::log_assert(
        index.x < prop<TableSize>().get().x &&
            index.y < prop<TableSize>().get().y,
        "TableSize::createNodeAt: Index ", index,
        " is out of bounds. Size: ", prop<TableSize>().get());

    inner_nodes_[index.x][index.y] = std::move(scene_node);
}

void TableNodeImp::for_each_table_innerSceneNode(
    htps::function<void(const htps::vector2dst&, const htps::sptr<SceneNode>&)>
        action)
{
    for (htps::size_type x{0}; x < inner_nodes_.size(); ++x)
    {
        for (htps::size_type y{0}; y < inner_nodes_[x].size(); ++y)
        {
            if (auto&& inner_node = inner_nodes_[x][y])
            {
                action(htps::vector2dst{x, y}, inner_node);
            }
        }
    }
}

}  // namespace haf::scene::nodes
