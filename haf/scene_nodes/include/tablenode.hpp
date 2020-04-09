#pragma once

#ifndef HAF_SCENE_TABLENODE_INCLUDE_HPP
#define HAF_SCENE_TABLENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/include/liblog.hpp>

namespace haf::scene::nodes
{
/// Class representing a SceneNode with table layout.
/// Properties of the table can be configured like size and so on.
template <typename T>
class TableNode : public SceneNode
{
public:
    using BaseClass = SceneNode;
    using ContainedElement = T;

    TableNode(SceneNode *parent, mtps::str name)
        : BaseClass{parent, std::move(name)} {}

    virtual ~TableNode() = default;

    void setTableSize(mtps::vector2dst ntableSize)
    {
        tableSize_.set(std::move(ntableSize));

        nodes_.resize(tableSize_().x);
        inner_nodes_.resize(tableSize_().x);

        for (auto &nodeColumn : nodes_)
        {
            nodeColumn.resize(tableSize_().y);
        }

        for (auto &nodeColumn : inner_nodes_)
        {
            nodeColumn.resize(tableSize_().y);
        }
    }

    mtps::vector2dst tableSize() const noexcept { return tableSize_(); }

    mtps::PropertyState<mtps::vector2df> sceneNodeSize;

    template <typename... Args>
    mtps::sptr<T> createNodeAt(const mtps::vector2dst &index, Args &&... args)
    {
        mtps::sptr<SceneNode> inner_node(createSceneNode<SceneNode>("inner_node" + make_str(index)));

        mtps::sptr<T> result(inner_node->createSceneNode<T>(std::forward<Args>(args)...));
        log_assert(index.x < tableSize().x && index.y < tableSize().y,
                       "TableSize::createNodeAt: Index ", index, " is out "
                                                                 "of bounds. Size: ",
                       tableSize());
        inner_nodes_[index.x][index.y] = std::move(inner_node);
        nodes_[index.x][index.y] = result;
        return result;
    }

    constexpr mtps::vector2df cellSize() const
    {
        return mtps::vector2df{sceneNodeSize() / static_cast<mtps::vector2df>(tableSize())};
    }

    constexpr mtps::sptr<T> operator()(const mtps::vector2dst &index) noexcept { return nodes_[index.x][index.y]; }
    constexpr const mtps::sptr<T> operator()(const mtps::vector2dst &index) const noexcept { return nodes_[index.x][index.y]; }
    constexpr mtps::sptr<T> nodeAt(const mtps::vector2dst &index) noexcept { return nodes_[index.x][index.y]; }
    constexpr const mtps::sptr<T> nodeAt(const mtps::vector2dst &index) const noexcept { return nodes_[index.x][index.y]; }

    constexpr void for_each_tableSceneNode(mtps::function<void(const mtps::vector2dst &, const mtps::sptr<T> &)> action)
    {
        for (mtps::size_type x{0}; x < nodes_.size(); ++x)
        {
            for (mtps::size_type y{0}; y < nodes_[x].size(); ++y)
            {
                if (mtps::sptr<T> node = nodes_[x][y])
                {
                    action(vector2dst{x, y}, node);
                }
            }
        }
    }

    constexpr void for_each_tableSceneNode_in_x(
        const mtps::size_type x, mtps::function<void(const mtps::size_type, const mtps::sptr<T> &)> action)
    {
        for_each_tableSceneNode([action, x](const mtps::vector2dst &pos, const mtps::sptr<T> &node)
        {
            if (pos.x == x)
            {
                action(pos.y, node);
            }
        });
    }

    constexpr void for_each_tableSceneNode_in_y(const mtps::size_type y, mtps::function<void(const mtps::size_type, const mtps::sptr<T> &)> action)
    {
        for_each_tableSceneNode([action, y](const mtps::vector2dst &pos, const mtps::sptr<T> &node)
        {
            if (pos.y == y)
            {
                action(pos.x, node);
            }
        });
    }

    void update() override
    {
        BaseClass::update();

        // Update row and column size
        if (ps_readResetHasAnyChanged(sceneNodeSize, tableSize_))
        {
            const mtps::vector2df cell_size{cellSize()};
            for_each_table_innerSceneNode([this, cell_size](const mtps::vector2dst &p, const auto &n)
            {
                n->position = cell_size * static_cast<mtps::vector2df>(p);
            });
        }
    }

private:
    constexpr void for_each_table_innerSceneNode(
        mtps::function<void(const mtps::vector2dst &, const mtps::sptr<SceneNode> &)> action)
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

    mtps::vector<mtps::vector_shared_pointers<SceneNode>> inner_nodes_;
    mtps::vector<mtps::vector_shared_pointers<T>> nodes_;
    mtps::PropertyState<mtps::vector2dst> tableSize_;
};
} // namespace haf::scene::nodes

#endif
