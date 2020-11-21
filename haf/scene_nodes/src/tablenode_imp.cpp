#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <haf/scene_nodes/include/tablenode_imp.hpp>

namespace haf::scene::nodes
{

TableNodeImp::~TableNodeImp() = default;

mtps::vector2df TableNodeImp::cellSize() const
{
    return mtps::vector2df{
        prop<SceneNodeSize>().get() /
        static_cast<mtps::vector2df>(prop<TableSize>().get())};
}

void TableNodeImp::update()
{
    BaseClass::update();

    updateTableSizeIfNecessary();

    // Update row and column size
    if (prop<SceneNodeSize>().readResetHasChanged())
    {
        mtps::vector2df const& cell_size{cellSize()};
        for_each_table_innerSceneNode(
            [this, cell_size](mtps::vector2dst const& p, const mtps::sptr<SceneNode>& n) {
                n->prop<Position>().set(cell_size * static_cast<mtps::vector2df>(p));
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

void TableNodeImp::setTableSize(mtps::vector2dst const ntableSize)
{
    inner_nodes_.resize(ntableSize.x);

    for (auto& nodeColumn : inner_nodes_)
    {
        nodeColumn.resize(ntableSize.y);
    }
}

void TableNodeImp::setInnerSceneNodeAt(mtps::vector2dst const index,
                                       mtps::sptr<SceneNode> scene_node)
{
    LogAsserter::log_assert(
        index.x < prop<TableSize>().get().x &&
            index.y < prop<TableSize>().get().y,
        "TableSize::createNodeAt: Index ", index,
        " is out of bounds. Size: ", prop<TableSize>().get());

    inner_nodes_[index.x][index.y] = std::move(scene_node);
}

void TableNodeImp::for_each_table_innerSceneNode(
    mtps::function<void(const mtps::vector2dst&, const mtps::sptr<SceneNode>&)>
        action)
{
    for (mtps::size_type x{0}; x < inner_nodes_.size(); ++x)
    {
        for (mtps::size_type y{0}; y < inner_nodes_[x].size(); ++y)
        {
            if (auto&& inner_node = inner_nodes_[x][y])
            {
                action(mtps::vector2dst{x, y}, inner_node);
            }
        }
    }
}

}  // namespace haf::scene::nodes
