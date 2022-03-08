#ifndef HAF_SCENE_NODE_TABLE_INCLUDE_HPP
#define HAF_SCENE_NODE_TABLE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/scene_nodes/scene_node_table_imp.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene::nodes
{
/**
 * @brief Class representing a SceneNode with table layout.
 * Properties of the table can be configured like size and so on.
 * @tparam T
 */
template <typename T>
class HAF_API TableNode : public TableNodeImp
{
    using BaseClass = TableNodeImp;

public:
    using ContainedElement = T;

    using BaseClass::BaseClass;
    using BaseClass::prop;

    htps::sptr<T> createNodeAt(htps::vector2dst const& index,
                               htps::str const& name)
    {
        return nodeAt(index) = createInnerSceneNodeAt(index, name)
                                   ->createSceneNode<T>("inner_inner_node");
    }

    void createNodeAtNoReturn(htps::vector2dst const& index,
                                       htps::str const& name) override
    {
        (void)(nodeAt(index) = createInnerSceneNodeAt(index, name)
                                   ->createSceneNode<T>("inner_inner_node"));
    }

    constexpr htps::sptr<T>& operator()(htps::vector2dst const& index)
    {
        return nodeAt(index);
    }

    constexpr htps::sptr<T const> const operator()(
        htps::vector2dst const& index) const noexcept
    {
        return nodeAt(index);
    }

    constexpr htps::sptr<T>& nodeAt(htps::vector2dst const& index)
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
        for (htps::size_type x{0U}; x < nodes_.size(); ++x)
        {
            for (htps::size_type y{0U}; y < nodes_[x].size(); ++y)
            {
                if (htps::sptr<T> & node{nodes_[x][y]}; node)
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
        for_each_tableSceneNode([&action, x](htps::vector2dst const& pos,
                                             htps::sptr<T> const& node) {
            if (pos.x == x)
            {
                action(pos.y, node);
            }
        });
    }

    constexpr void for_each_tableSceneNode_in_y(
        htps::size_type const y,
        htps::function<void(htps::size_type const, htps::sptr<T> const&)> const
            action)
    {
        for_each_tableSceneNode([&action, y](htps::vector2dst const& pos,
                                             htps::sptr<T> const& node) {
            if (pos.y == y)
            {
                action(pos.x, node);
            }
        });
    }

    template <typename PropertyType>
    auto* setTableNodeProperty(typename PropertyType::value_type const& value)
    {
        for_each_tableSceneNode(
            [&value](auto const&, htps::sptr<T> const& node) {
                node->template prop<PropertyType>().set(value);
            });
        return this;
    }

private:
    void setTableSize(htps::vector2dst const ntableSize) override
    {
        BaseClass::setTableSize(ntableSize);
        nodes_.resize(ntableSize.x);

        for (auto&& nodeColumn : nodes_)
        {
            nodeColumn.resize(ntableSize.y);
        }
    }

    htps::vector<htps::vector_shared_pointers<T>> nodes_;
};

}  // namespace haf::scene::nodes

#endif
