HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_NODE_TABLE_INCLUDE_HPP
#define HAF_SCENE_NODE_TABLE_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <htypes/include/connection.hpp>
#include <htypes/include/properties/properties.hpp>
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

    htps::emitter<htps::vector2dst, htps::sptr<T> const&> onTableNodeCreated;

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

    template <template <typename> typename PropertyType,
              typename PropertyValue,
              typename ObjectType>
    constexpr void set_property_for_each_table_node(
        PropertyType<PropertyValue>(ObjectType::*property_v),
        PropertyValue const& value)
    {
        for_each_tableSceneNode(
            [&value, property_v](htps::vector2dst const&,
                                 htps::sptr<T> const& node) {
                set_property(node, property_v, value);
            });
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

private:
    virtual void tableNodeCreated(htps::vector2dst, htps::sptr<T> const&) {}

    void createNodeAt(htps::vector2dst const& index) override final
    {
        auto createdNode{
            innerSceneNodeAt(index)->createSceneNode<T>("inner_inner_node")};
        nodeAt(index) = createdNode;
        onTableNodeCreated(index, nodeAt(index));
        tableNodeCreated(index, nodeAt(index));
    }

    void setTableSize(htps::vector2dst const ntableSize) override final
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
