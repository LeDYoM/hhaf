#pragma once

#ifndef LIB_SCENE_TABLENODE_INCLUDE_HPP__
#define LIB_SCENE_TABLENODE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene::nodes
{
	template <typename T>
	class TableNode : public SceneNode
	{
	public:
		TableNode(SceneNode *parent, str name) : SceneNode{ parent, name } {}
		virtual ~TableNode() = default;

		Property<vector2du32> tableSize = [this]()
		{
			setNeedsUpdate();

			m_nodes.resize(tableSize().x);
			for (auto& nodeColumn : m_nodes) {
				nodeColumn.resize(tableSize().y);
			}
		};

		Property<vector2df> sceneNodeSize = [this]()
		{
			setNeedsUpdate();
		};

		template <typename... Args>
		sptr<T> createNodeAt(const vector2du32 &index, Args&&... args)
		{
			setNeedsUpdate();
			sptr<T> result(createSceneNode<T>(std::forward<Args>(args)...));
			assert_release(index.x < tableSize().x && index.y < tableSize().y,"Out of bounds");
			m_nodes[index.x][index.y] = result;
			addSceneNode(result);
			return result;
		}

		constexpr sptr<T> operator()(const vector2du32 &index) noexcept { return m_nodes[index.x][index.y]; }
		constexpr const sptr<T> operator()(const vector2du32 &index) const noexcept { return m_nodes[index.x][index.y]; }
		constexpr sptr<T> nodeAt(const vector2du32 &index) noexcept { return m_nodes[index.x][index.y]; }
		constexpr const sptr<T> nodeAt(const vector2du32 &index) const noexcept { return m_nodes[index.x][index.y]; }

		constexpr void for_each_tableSceneNode(function<void(const vector2du32 &, const sptr<T> &)> action) {
			for (size_type x{ 0 }; x < m_nodes.size(); ++x) {
				for (size_type y{ 0 }; y < m_nodes[x].size(); ++y) {
					if (sptr<T> node = m_nodes[x][y]) {
						action(vector2du32{ x,y }, node);
					}
				}
			}
		}

		constexpr void for_each_tableSceneNode_in_x(const size_type x, function<void(const size_type, const sptr<T> &)> action) {
			for_each_tableSceneNode([action,x](const vector2du32 &pos, const sptr<T> &node) {
				if (pos.x == x) {
					action(pos.y, node);
				}
			});
		}

		constexpr void for_each_tableSceneNode_in_y(const size_type y, function<void(const size_type, const sptr<T> &)> action) {
			for_each_tableSceneNode([action, y](const vector2du32 &pos, const sptr<T> &node) {
				if (pos.y == y) {
					action(pos.x, node);
				}
			});
		}

		void update() override {
			SceneNode::update();
			// Update row and column size
			const vector2df nodeSize{ sceneNodeSize() / static_cast<vector2df>(tableSize()) };
					
			for_each_tableSceneNode([this, nodeSize](const vector2du32 &p, const sptr<T> &n) {
				n->position = nodeSize * static_cast<vector2df>(p);
			});
		}

	private:
		vector<vector_shared_pointers<T>> m_nodes;
	};
}

#endif
