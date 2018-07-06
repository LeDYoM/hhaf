#pragma once

#ifndef LIB_SCENE_TABLENODE_INCLUDE_HPP__
#define LIB_SCENE_TABLENODE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene::nodes
{
	/**
	* Class representing a SceneNode with table layout.
	* Properties of the table can be configured like size and so on.
	*/
    template <typename T>
    class TableNode : public SceneNode
    {
    public:
        using BaseClass = SceneNode;
        using ContainedElement = T;

        TableNode(SceneNode *parent, str name, 
			vector2dst tableSize_ = vector2dst{})
			: BaseClass{ parent, std::move(name) } 
		{
            setTableSize(std::move(tableSize_));
		}

        virtual ~TableNode() = default;

        void setTableSize(vector2dst ntableSize)
        {
            m_tableSize.set(std::move(ntableSize));

            m_nodes.resize(m_tableSize().x);
            for (auto& nodeColumn : m_nodes) {
                nodeColumn.resize(m_tableSize().y);
            }
        }

        vector2dst tableSize() const { return m_tableSize(); }

        PropertyState<vector2df> sceneNodeSize;

        template <typename... Args>
        sptr<T> createNodeAt(const vector2dst &index, Args&&... args)
        {
            sptr<T> result(createSceneNode<T>(std::forward<Args>(args)...));
            assert_release(index.x < tableSize().x && index.y < tableSize().y,
                           "TableSize::createNodeAt: Index ", index, " is out "
                           "of bounds. Size: ",tableSize());
            m_nodes[index.x][index.y] = result;
            return result;
        }

		constexpr vector2df cellSize() const {
			return vector2df{ sceneNodeSize() / static_cast<vector2df>(tableSize()) };
		}

        constexpr sptr<T> operator()(const vector2dst &index) noexcept { return m_nodes[index.x][index.y]; }
        constexpr const sptr<T> operator()(const vector2dst &index) const noexcept { return m_nodes[index.x][index.y]; }
        constexpr sptr<T> nodeAt(const vector2dst &index) noexcept { return m_nodes[index.x][index.y]; }
        constexpr const sptr<T> nodeAt(const vector2dst &index) const noexcept { return m_nodes[index.x][index.y]; }

        constexpr void for_each_tableSceneNode(function<void(const vector2dst &, const sptr<T> &)> action)
        {
            for (size_type x{ 0 }; x < m_nodes.size(); ++x) {
                for (size_type y{ 0 }; y < m_nodes[x].size(); ++y) {
                    if (sptr<T> node = m_nodes[x][y]) {
                        action(vector2dst{ x,y }, node);
                    }
                }
            }
        }

        constexpr void for_each_tableSceneNode_in_x(
                const size_type x, function<void(const size_type, const sptr<T> &)> action)
        {
            for_each_tableSceneNode([action,x](const vector2dst &pos, const sptr<T> &node) {
                if (pos.x == x) {
                    action(pos.y, node);
                }
            });
        }

        constexpr void for_each_tableSceneNode_in_y(const size_type y, function<void(const size_type, const sptr<T> &)> action) {
            for_each_tableSceneNode([action, y](const vector2dst &pos, const sptr<T> &node) {
                if (pos.y == y) {
                    action(pos.x, node);
                }
            });
        }

        void update() override {
            BaseClass::update();
            // Update row and column size

            if (ps_readResetHasChanged(sceneNodeSize, m_tableSize))
            {
                const vector2df nodeSize{ sceneNodeSize() / static_cast<vector2df>(tableSize()) };

                for_each_tableSceneNode([this, nodeSize](const vector2dst &p, const sptr<T> &n) {
                    n->position = nodeSize * static_cast<vector2df>(p);
                });
            }
        }

    private:
        vector<vector_shared_pointers<T>> m_nodes;
        PropertyState<vector2dst> m_tableSize;
    };
}

#endif
