#pragma once

#ifndef LIB_SCENE_TABLENODE_INCLUDE_HPP
#define LIB_SCENE_TABLENODE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene::nodes
{
/// Class representing a SceneNode with table layout.
/// Properties of the table can be configured like size and so on.
template <typename T>
class TableNode : public SceneNode
{
public:
    using BaseClass = SceneNode;
    using ContainedElement = T;

    TableNode(SceneNode *parent, str name)
        : BaseClass{parent, std::move(name)} {}

    virtual ~TableNode() = default;

    void setTableSize(vector2dst ntableSize)
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

    vector2dst tableSize() const noexcept { return tableSize_(); }

    PropertyState<vector2df> sceneNodeSize;

    template <typename... Args>
    sptr<T> createNodeAt(const vector2dst &index, Args &&... args)
    {
        sptr<SceneNode> inner_node(createSceneNode<SceneNode>("inner_node" + make_str(index)));

        sptr<T> result(inner_node->createSceneNode<T>(std::forward<Args>(args)...));
        log_assert(index.x < tableSize().x && index.y < tableSize().y,
                       "TableSize::createNodeAt: Index ", index, " is out "
                                                                 "of bounds. Size: ",
                       tableSize());
        inner_nodes_[index.x][index.y] = std::move(inner_node);
        nodes_[index.x][index.y] = result;
        return result;
    }

    constexpr vector2df cellSize() const
    {
        return vector2df{sceneNodeSize() / static_cast<vector2df>(tableSize())};
    }

    constexpr sptr<T> operator()(const vector2dst &index) noexcept { return nodes_[index.x][index.y]; }
    constexpr const sptr<T> operator()(const vector2dst &index) const noexcept { return nodes_[index.x][index.y]; }
    constexpr sptr<T> nodeAt(const vector2dst &index) noexcept { return nodes_[index.x][index.y]; }
    constexpr const sptr<T> nodeAt(const vector2dst &index) const noexcept { return nodes_[index.x][index.y]; }

    constexpr void for_each_tableSceneNode(function<void(const vector2dst &, const sptr<T> &)> action)
    {
        for (size_type x{0}; x < nodes_.size(); ++x)
        {
            for (size_type y{0}; y < nodes_[x].size(); ++y)
            {
                if (sptr<T> node = nodes_[x][y])
                {
                    action(vector2dst{x, y}, node);
                }
            }
        }
    }

    constexpr void for_each_tableSceneNode_in_x(
        const size_type x, function<void(const size_type, const sptr<T> &)> action)
    {
        for_each_tableSceneNode([action, x](const vector2dst &pos, const sptr<T> &node)
        {
            if (pos.x == x)
            {
                action(pos.y, node);
            }
        });
    }

    constexpr void for_each_tableSceneNode_in_y(const size_type y, function<void(const size_type, const sptr<T> &)> action)
    {
        for_each_tableSceneNode([action, y](const vector2dst &pos, const sptr<T> &node)
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
            const vector2df cell_size{cellSize()};
            for_each_table_innerSceneNode([this, cell_size](const vector2dst &p, const auto &n)
            {
                n->position = cell_size * static_cast<vector2df>(p);
            });
        }
    }

private:
    constexpr void for_each_table_innerSceneNode(
        function<void(const vector2dst &, const sptr<SceneNode> &)> action)
    {
        for (size_type x{0}; x < inner_nodes_.size(); ++x)
        {
            for (size_type y{0}; y < inner_nodes_[x].size(); ++y)
            {
                if (auto&& inner_node = inner_nodes_[x][y])
                {
                    action(vector2dst{x, y}, inner_node);
                }
            }
        }
    }

    vector<vector_shared_pointers<SceneNode>> inner_nodes_;
    vector<vector_shared_pointers<T>> nodes_;
    PropertyState<vector2dst> tableSize_;
};
} // namespace lib::scene::nodes

#endif
