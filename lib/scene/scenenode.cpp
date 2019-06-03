#include "scenenode.hpp"
#include "scene.hpp"

#include <lib/scene/renderizables/renderizable.hpp>

#include <logger/include/log.hpp>

#include "scenemanager.hpp"
#include "scenenodeblob.hpp"

namespace lib::scene
{
    SceneNode::SceneNode(SceneNode *const parent, str name)
        : core::HasName{ std::move(name) }, DataWrapperCreator{ this}, 
        ComponentContainer{ this }, SceneNodeBlob{ *this },
        visible{ true }, m_parent{ parent }
    {
    }

    SceneNode::~SceneNode() = default;

    void SceneNode::render(bool parentTransformationChanged)
    {
        if (visible()) 
        {
            // Update the node components
            updateComponents();

            // Update node
            update();

            if (transformationNeedsUpdate()) {
                parentTransformationChanged = true;
            }

			if (parentTransformationChanged) {
				updateGlobalTransformation(m_parent ? m_parent->globalTransform() : Transform{});
			}

            for (auto&& renderizable : m_renderNodes) {
                renderizable->render();
            }

            for (auto&& group : m_groups) {
                group->render(parentTransformationChanged);
            }
        }
    }

    bool SceneNode::moveLastBeforeNode(const sptr<SceneNode> &beforeNode)
    {
        assert_release(!m_groups.empty(), "Cannot moveLastInsertedBeforeNode on empty container");
        if (!beforeNode) return false;

        // Find the node to swap before to
        auto iterator (std::find(m_groups.begin(), m_groups.end(),beforeNode));

        // If beforeNode not found, nothing to do
        if (iterator == m_groups.end()) return false;

        // If beforeNode is the last element, nothing to do
        if (iterator == std::prev(m_groups.end())) return false;

        auto last(std::prev(m_groups.end()));

        // Do not swap yourself
        if (*iterator == *last) return false;

        // Swap the iterators
        std::swap(*iterator, *last);
        return true;
    }

    void SceneNode::addSceneNode(sptr<SceneNode> node)
    {
        m_groups.push_back(node);
        node->m_parent = this;
        node->onCreated();
    }

    void SceneNode::removeSceneNode(sptr<SceneNode> element)
    {
        assert_debug(element.get() != nullptr, "Received empty scene node to be deleted");
        assert_release(this != element.get(), "Cannot delete myself from myself");
        assert_debug(this == element->parent()," You must call removeSceneNode from the parent node");

        m_groups.remove_value(element);
    }

    void SceneNode::clearAll()
    {
        clearSceneNodes();
        clearComponents();
    }

    void SceneNode::clearSceneNodes()
    {
        m_groups.clear();
    }
}
