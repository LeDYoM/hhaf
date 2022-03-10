#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/scene_nodes/scene_node_table_imp.hpp>

using namespace htps;

namespace haf::scene::nodes
{
htps::vector2df TableNodeImp::cellSize() const
{
    /*
        return htps::vector2df{
            prop<SceneNodeSize>().get() /
            static_cast<htps::vector2df>(prop<TableSize>().get())};
    */
    return htps::vector2df{
        1.0F / static_cast<htps::vector2df>(prop<TableSize>().get())};
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
            [this, cell_size](htps::vector2dst const& p,
                              ContainedType_t& node) {
                node->prop<Position>().set(cell_size *
                                           static_cast<htps::vector2df>(p));
            });
    }
}

bool TableNodeImp::nodeTableCreated(vector2dst const& index) const
{
    return inner_nodes_.size() > index.x &&
        inner_nodes_[index.x].size() > index.y;
}

void TableNodeImp::update2()
{
    if (name() == "score")
    {
        int a = 0;
        (void)a;
    }
    updateTableSizeIfNecessary();

    // Update row and column size
    if (prop<TableSize>().readResetHasChanged())
    {
        auto const tableSize{prop<TableSize>().get()};

        // Create the nodes to render the tiles
        for (size_type y{0U}; y < tableSize.y; ++y)
        {
            for (size_type x{0U}; x < tableSize.x; ++x)
            {
                (void)(createInnerSceneNodeAt({x, y},
                                              make_str("inner_node_", x, y)));
            }
        }

        auto const& cell_size{cellSize()};
        auto const half_cell_size{cell_size / 2.0F};
        auto const left_top{sceneView().leftTop()};
        auto const left_top_plus_half_size{vector2df{-0.5F, -0.5F} +
                                           half_cell_size};
        for_each_table_innerSceneNode(
            [this, &cell_size, &left_top_plus_half_size](
                htps::vector2dst const& p,
                const htps::sptr<TransformableSceneNode>& node) {
                if (node->sceneNodes().empty())
                {
                    createNodeAtNoReturn({p.x, p.y},
                                         make_str(name(), "_", p.x, p.y));
                }

                if (prop<ScaleGroup>()())
                {
                    node->prop<Scale>().set(cell_size);
                }

                if (prop<MoveGroup>()())
                {
                    node->prop<Position>().set(
                        left_top_plus_half_size +
                        (cell_size * static_cast<htps::vector2df>(p)));
                }
            });
    }
}

TableNodeImp::ContainedType_t TableNodeImp::createInnerSceneNodeAt(
    htps::vector2dst const index,
    htps::str const& name)
{
    ContainedType_t inner_node{createSceneNode<TransformableSceneNode>(
        make_str(name, "_inner_node", index))};

    setInnerSceneNodeAt(index, inner_node);
    onInnerNodeCreated(index, inner_node);
    return inner_node;
}

void TableNodeImp::updateTableSizeIfNecessary()
{
    if (prop<TableSize>().hasChanged())
    {
        setTableSize(prop<TableSize>().get());
        prop<SceneNodeSize>().setChanged();
    }
}

void TableNodeImp::setTableSize(htps::vector2dst const ntableSize)
{
    inner_nodes_.resize(ntableSize.x);

    for (auto&& nodeColumn : inner_nodes_)
    {
        nodeColumn.resize(ntableSize.y);
    }
}

void TableNodeImp::setInnerSceneNodeAt(htps::vector2dst const index,
                                       ContainedType_t& scene_node)
{
    LogAsserter::log_assert(
        index.x < prop<TableSize>().get().x &&
            index.y < prop<TableSize>().get().y,
        "TableSize::createNodeAt: Index ", index,
        " is out of bounds. Size: ", prop<TableSize>().get());

    inner_nodes_[index.x][index.y] = scene_node;
}

void TableNodeImp::for_each_table_innerSceneNode(
    htps::function<void(htps::vector2dst const&, ContainedType_t&)> action)
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
