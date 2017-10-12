#pragma once

#ifndef LIB_SCENE_TABLENODE_INCLUDE_HPP__
#define LIB_SCENE_TABLENODE_INCLUDE_HPP__

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

				inline void setSize(const vector2du32 &nSize)
				{
					setNeedsUpdate();

					m_nodes.resize(nSize.x);
					for (auto nodeColumn : m_nodes) {
						nodeColumn.resize(nSize.y);
					}
				}

				template <typename... Args>
				sptr<T> createNodeAt(const vector2du32 &index, Args&&... args)
				{
					setNeedsUpdate();
					auto result(createSceneNode<T>(std::forward<Args>(args)...));
					m_nodes[index.x][index.y] = result;
					addSceneNode(result);
					return result;
				}


				inline sptr<T> operator()(const vector2du32 &index) noexcept { return m_nodes[index.x][index.y]; }
				inline const sptr<T> operator()(const vector2du32 &index) const noexcept { return m_nodes[index.x][index.y]; }

				virtual void update() override {

				}

				Property<Rectf32> bound
			private:
				vector<vector_shared_pointers<T>> m_nodes;
			};
		}
	}
}

#endif
