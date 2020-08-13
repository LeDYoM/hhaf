#pragma once

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

    ~TableNode() override = default;

    mtps::sptr<T> createNodeAt(const mtps::vector2dst& index,
                               const mtps::str& name)
    {
        mtps::sptr<SceneNode> inner_node(
            createSceneNode<SceneNode>(name + "inner_node" + make_str(index)));

        mtps::sptr<T> result(
            inner_node->createSceneNode<T>("inner_inner_node"));
     
        updateTableSizeIfNecessary();

        BaseClass::setInnerSceneNodeAt(index, std::move(inner_node));
        nodes_[index.x][index.y] = result;
        return result;
    }

    constexpr mtps::sptr<T> operator()(mtps::vector2dst const& index) noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr const mtps::sptr<T> operator()(
        mtps::vector2dst const& index) const noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr mtps::sptr<T> nodeAt(mtps::vector2dst const& index) noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr const mtps::sptr<T> nodeAt(
        mtps::vector2dst const& index) const noexcept
    {
        return nodes_[index.x][index.y];
    }

    constexpr void for_each_tableSceneNode(
        mtps::function<void(mtps::vector2dst const&, mtps::sptr<T> const&)> const
            action)
    {
        for (mtps::size_type x{0}; x < nodes_.size(); ++x)
        {
            for (mtps::size_type y{0}; y < nodes_[x].size(); ++y)
            {
                if (mtps::sptr<T> node = nodes_[x][y]; node)
                {
                    action(mtps::vector2dst{x, y}, node);
                }
            }
        }
    }

    constexpr void for_each_tableSceneNode_in_x(
        mtps::size_type const x,
        mtps::function<void(const mtps::size_type, mtps::sptr<T> const&)> const
            action)
    {
        for_each_tableSceneNode([action, x](mtps::vector2dst const& pos,
                                            mtps::sptr<T> const& node) {
            if (pos.x == x)
            {
                action(pos.y, node);
            }
        });
    }

    constexpr void for_each_tableSceneNode_in_y(
        const mtps::size_type y,
        mtps::function<void(const mtps::size_type, const mtps::sptr<T>&)> const
            action)
    {
        for_each_tableSceneNode([action, y](const mtps::vector2dst& pos,
                                            const mtps::sptr<T>& node) {
            if (pos.y == y)
            {
                action(pos.x, node);
            }
        });
    }

private:
    void setTableSize(mtps::vector2dst ntableSize) override
    {
        BaseClass::setTableSize(ntableSize);
        nodes_.resize(ntableSize.x);

        for (auto& nodeColumn : nodes_)
        {
            nodeColumn.resize(ntableSize.y);
        }
    }

    mtps::vector<mtps::vector_shared_pointers<T>> nodes_;
};
}  // namespace haf::scene::nodes

#endif
