#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/scene_components/table.hpp>
#include <haf/include/scene/scene_node.hpp>

using namespace htps;
using namespace fmath;

namespace haf::scene
{
fmath::vector2df Table::cellSize() const
{
    return fmath::vector2df{1.0F / static_cast<fmath::vector2df>(TableSize())};
}

void Table::update()
{
    BaseClass::update();
    createTableNodesIfNecessary();
}

void Table::createTableNodesIfNecessary()
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
                if (m_inner_nodes[x][y] == nullptr)
                {
                    createInnerSceneNodeAt({x, y},
                                           make_str("inner_node_", x, y));
                }
            }
        }

        auto const& cell_size{cellSize()};
        auto const half_cell_size{cell_size / 2.0F};
        auto const left_top_plus_half_size{vector2df{-0.5F, -0.5F} +
                                           half_cell_size};
        for_each_table_innerSceneNode(
            [this, &cell_size, &left_top_plus_half_size](
                fmath::vector2dst const& p, const htps::sptr<SceneNode>& node) {
                if (node->sceneNodes().empty())
                {
                    createNodeAt({p.x, p.y});
                }

                node->Scale = cell_size;

                node->Position = left_top_plus_half_size +
                    (cell_size * static_cast<fmath::vector2df>(p));
                attachedNode()->Position = {0.0F, 0.0F};
            });
        onAllTableElementsCreated(TableSize());
        allTableElementsCreated(TableSize());
    }
}

bool Table::nodeTableCreated(vector2dst const& index) const
{
    return m_inner_nodes.size() > index.x &&
        m_inner_nodes[index.x].size() > index.y;
}

void Table::createInnerSceneNodeAt(vector2dst const index, str const& name)
{
    LogAsserter::log_assert(m_inner_nodes[index.x][index.y] == nullptr,
                            "Node already created");
    sptr<SceneNode> inner_node{attachedNode()->createSceneNode(name)};

    setInnerSceneNodeAt(index, inner_node);
    onInnerNodeCreated(index, inner_node);
}

sptr<SceneNode> Table::innerSceneNodeAt(fmath::vector2dst const index) const
{
    return m_inner_nodes[index.x][index.y];
}

void Table::updateTableSizeIfNecessary()
{
    if (TableSize.hasChanged())
    {
        setTableSize(TableSize());
    }
}

void Table::onAllTableElementsCreated(vector2dst const)
{}

void Table::setTableSize(vector2dst const ntableSize)
{
    m_inner_nodes.resize(ntableSize.x);

    for (auto&& nodeColumn : m_inner_nodes)
    {
        nodeColumn.resize(ntableSize.y);
    }
}

void Table::setInnerSceneNodeAt(vector2dst const index,
                                sptr<SceneNode>& scene_node)
{
    LogAsserter::log_assert(index.x < TableSize().x && index.y < TableSize().y,
                            "TableSize::createNodeAt: Index ", index,
                            " is out of bounds. Size: ", TableSize());

    m_inner_nodes[index.x][index.y] = scene_node;
}

void Table::for_each_table_innerSceneNode(
    function<void(vector2dst const&, sptr<SceneNode>&)> action)
{
    for (htps::size_type x{0}; x < m_inner_nodes.size(); ++x)
    {
        for (htps::size_type y{0}; y < m_inner_nodes[x].size(); ++y)
        {
            if (auto&& inner_node = m_inner_nodes[x][y])
            {
                action(fmath::vector2dst{x, y}, inner_node);
            }
        }
    }
}

}  // namespace haf::scene
