#pragma once

#ifndef LIB_SCENE_TABLENODE_INCLUDE_HPP__
#define LIB_SCENE_TABLENODE_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib
{
	namespace scene
	{
		namespace nodes
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
					for (auto nodeColumn : m_nodes) {
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
					m_nodes[index.x][index.y] = result;
					addSceneNode(result);
					return result;
				}

				constexpr sptr<T> operator()(const vector2du32 &index) noexcept { return m_nodes[index.x][index.y]; }
				constexpr const sptr<T> operator()(const vector2du32 &index) const noexcept { return m_nodes[index.x][index.y]; }
				constexpr sptr<T> operator()(const size_type indexx, const size_type &indexy) noexcept { return m_nodes[indexx][indexy]; }
				constexpr const sptr<T> operator()(const size_type indexx, const size_type &indexy) const noexcept { return m_nodes[indexx][indexy]; }

				constexpr vector_shared_pointers<T> getY(const size_type indexx) const noexcept { return m_nodes[indexx]; }
				constexpr vector_shared_pointers<T> getX(const size_type indexy) const noexcept { 
					vector_shared_pointers<T> result(tableSize().y);
					for (auto &nodeRow : m_nodes[indexy]) {
						result.push_back(nodeRow);
					}

					return result;
				}

				constexpr void for_each_tableSceneNode(function<void(const vector2du32 &, const sptr<T> &)> action)
				{
					for (size_t x{ 0 }; x < m_nodes.size(); ++x) {
						for (size_t y{ 0 }; y < m_nodes[x].size(); ++y) {
							action({ x,y }, m_nodes[x][y]);
						}
					}
				}

				virtual void update() override {
					SceneNode::update();
					// Update row and column size
					const vector2df nodeSize{ sceneNodeSize() / static_cast<vector2df>(tableSize()) };
					
					for_each_tableSceneNode([this, nodeSize](const vector2du32 &, const sptr<T> &) {
//						n->pos
//						n->position = nodesSize * static_cast<vector2df>(p);
					});
				}

			private:
				vector<vector_shared_pointers<T>> m_nodes;
			};
		}
	}
}

#endif
