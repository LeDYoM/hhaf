#include <htypes/include/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/scene_components/table_node_imp.hpp>

using namespace htps;

namespace haf::scene
{
htps::vector2df TableNodeImp::cellSize() const
{
    return htps::vector2df{1.0F / static_cast<htps::vector2df>(TableSize())};
}

void TableNodeImp::update()
{
    BaseClass::update();
    createTableNodesIfNecessary();
}

void TableNodeImp::createTableNodesIfNecessary()
{
    updateTableSizeIfNecessary();

    // Update row and column size
    if (TableSize.readResetHasChanged())
    {
        auto const tableSize{TableSize()};

        // Create the nodes to render the tiles
        for (size_type y{0U}; y < tableSize.y; ++y)
        {
            for (size_type x{0U}; x < tableSize.x; ++x)
            {
                if (inner_nodes_[x][y] == nullptr)
                {
                    (void)(createInnerSceneNodeAt(
                        {x, y}, make_str("inner_node_", x, y)));
                }
            }
        }

        auto const& cell_size{cellSize()};
        auto const half_cell_size{cell_size / 2.0F};
        auto const left_top_plus_half_size{vector2df{-0.5F, -0.5F} +
                                           half_cell_size};
        for_each_table_innerSceneNode([this, &cell_size,
                                       &left_top_plus_half_size](
                                          htps::vector2dst const& p,
                                          const htps::sptr<
                                              TransformableSceneNode>& node) {
            if (node->sceneNodes().empty())
            {
                createNodeAt({p.x, p.y});
            }

            node->Scale = cell_size;

            node->Position = left_top_plus_half_size +
                (cell_size * static_cast<htps::vector2df>(p));
//            m_transformableComponent->Position = {0.0F, 0.0F};
        });
        allTableElementsCreated(TableSize());
    }
}

bool TableNodeImp::nodeTableCreated(vector2dst const& index) const
{
    return inner_nodes_.size() > index.x &&
        inner_nodes_[index.x].size() > index.y;
}

TableNodeImp::ContainedType_t TableNodeImp::createInnerSceneNodeAt(
    htps::vector2dst const index,
    htps::str const& name)
{
    LogAsserter::log_assert(inner_nodes_[index.x][index.y] == nullptr,
                            "Node already created");
    ContainedType_t inner_node{
        attachedNode()->createSceneNode<TransformableSceneNode>(
            make_str(name, "_inner_node", index))};

    setInnerSceneNodeAt(index, inner_node);
    onInnerNodeCreated(index, inner_node);
    return inner_node;
}

TableNodeImp::ContainedType_t TableNodeImp::innerSceneNodeAt(
    htps::vector2dst const index) const
{
    return inner_nodes_[index.x][index.y];
}

void TableNodeImp::updateTableSizeIfNecessary()
{
    if (TableSize.hasChanged())
    {
        setTableSize(TableSize());
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
    LogAsserter::log_assert(index.x < TableSize().x && index.y < TableSize().y,
                            "TableSize::createNodeAt: Index ", index,
                            " is out of bounds. Size: ", TableSize());

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

void TableNodeImp::addRequirements(component::ComponentRequirements& )
{
//    cReq.component(m_transformableComponent);
}

}  // namespace haf::scene
