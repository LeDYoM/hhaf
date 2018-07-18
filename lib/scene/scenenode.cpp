#include "scenenode.hpp"
#include <lib/scene/renderizables/renderizable.hpp>
#include "scene.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/include/core/log.hpp>

#include "scenemanager.hpp"

namespace lib::scene
{
    SceneNode::SceneNode(SceneNode *const parent, str name)
        : core::HasName{ std::move(name) }, ComponentContainer{ this }, 
        visible{ true }, m_parent{ parent }
    {
//        log_debug_info("Creating object: ", typeid(*this).name());
    }

    SceneNode::~SceneNode() 
	{ 
//        log_debug_info("Destroying ", typeid(*this).name());
        clearAll();
    }

    void SceneNode::render(bool parentTransformationChanged)
    {
        if (visible()) {
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

    Rectf32 SceneNode::scenePerspective()
    {
        return sceneManager().viewRect();
    }

    bool SceneNode::moveLastBeforeNode(const sptr<SceneNode> &beforeNode)
    {
        __ASSERT(!m_groups.empty(), "Cannot moveLastInsertedBeforeNode on empty container");
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

    void SceneNode::for_each_node(function<void(const sptr<Renderizable>&)> action) const
    {
        std::for_each(m_renderNodes.cbegin(), m_renderNodes.cend(), action);
    }

    void SceneNode::for_each_group(function<void(const sptr<SceneNode>&)> action) const
    {
        std::for_each(m_groups.cbegin(), m_groups.cend(), action);
    }

    void SceneNode::addRenderizable(sptr<Renderizable> newElement)
    {
        m_renderNodes.push_back(std::move(newElement));
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

    void SceneNode::removeRenderizable(sptr<Renderizable> element)
    {
        assert_debug(element.get() != nullptr, "Received empty renderizable node to be deleted");

        m_renderNodes.remove_value(element);
    }

    void SceneNode::clearAll()
    {
        clearNodes();
        clearComponents();
    }

    void SceneNode::clearRenderizables()
    {
        m_renderNodes.clear();
    }

    void SceneNode::clearSceneNodes()
    {
        m_groups.clear();
    }

    void SceneNode::clearNodes()
    {
        clearRenderizables();
        clearSceneNodes();
    }
}
