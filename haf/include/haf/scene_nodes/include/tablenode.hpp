#ifndef HAF_SCENE_TABLENODE_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_INCLUDE_HPP

#include <haf/scene_nodes/include/tablenode_imp.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene::nodes
{
/// Class representing a SceneNode with table layout.
/// Properties of the table can be configured like size and so on.
template <typename T>
class TableNode : public TableNodeImp
{
public:
    using BaseClass        = TableNodeImp;
    using ContainedElement = T;

    using BaseClass::BaseClass;
    using BaseClass::prop;

    htps::sptr<T> createNodeAt(const htps::vector2dst& index,
                               const htps::str& name)
    {
        htps::sptr<SceneNode> inner_node(
            createSceneNode<SceneNode>(name + "inner_node" + make_str(index)));

        htps::sptr<T> result(
            inner_node->createSceneNode<T>("inner_inner_node"));

        updateTableSizeIfNecessary();

        BaseClass::setInnerSceneNodeAt(index, std::move(inner_node));
        nodes_[index.x][index.y] = result;
        return result;
    }

    constexpr htps::sptr<T> operator()(htps::vector2dst const& index) noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr htps::sptr<T const> const operator()(
        htps::vector2dst const& index) const noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr htps::sptr<T> nodeAt(htps::vector2dst const& index) noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr htps::sptr<T const> const nodeAt(
        htps::vector2dst const& index) const noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr void for_each_tableSceneNode(
        htps::function<void(htps::vector2dst const&,
                            htps::sptr<T> const&)> const action)
    {
        for (htps::size_type x{0}; x < nodes_.size(); ++x)
        {
            for (htps::size_type y{0}; y < nodes_[x].size(); ++y)
            {
                if (htps::sptr<T> node = nodes_[x][y]; node)
                {
                    action(htps::vector2dst{x, y}, node);
                }
            }
        }
    }

    constexpr void for_each_tableSceneNode_in_x(
        htps::size_type const x,
        htps::function<void(const htps::size_type, htps::sptr<T> const&)> const
            action)
    {
        for_each_tableSceneNode([action, x](htps::vector2dst const& pos,
                                            htps::sptr<T> const& node) {
            if (pos.x == x)
            {
                action(pos.y, node);
            }
        });
    }

    constexpr void for_each_tableSceneNode_in_y(
        const htps::size_type y,
        htps::function<void(const htps::size_type, const htps::sptr<T>&)> const
            action)
    {
        for_each_tableSceneNode([action, y](const htps::vector2dst& pos,
                                            const htps::sptr<T>& node) {
            if (pos.y == y)
            {
                action(pos.x, node);
            }
        });
    }

private:
    void setTableSize(htps::vector2dst ntableSize) override
    {
        BaseClass::setTableSize(ntableSize);
        nodes_.resize(ntableSize.x);

        for (auto& nodeColumn : nodes_)
        {
            nodeColumn.resize(ntableSize.y);
        }
    }

    htps::vector<htps::vector_shared_pointers<T>> nodes_;
};

}  // namespace haf::scene::nodes

#endif
