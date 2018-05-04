#include "scenenode.hpp"
#include "renderizable.hpp"
#include "scene.hpp"

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <mtypes/include/log.hpp>
#include "scenemanager.hpp"

namespace lib::scene
{
    SceneNode::SceneNode(SceneNode *const parent, str name)
        : core::HasName{ std::move(name) }, ComponentContainer{ this }, 
        visible{ true }, m_parent{ parent }
    {
//        log_debug_info("Creating object: ", typeid(*this).name());
    }

    SceneNode::~SceneNode() { 
//        log_debug_info("Destroying ", typeid(*this).name());
        clearAll();
    }

    void SceneNode::render(bool parentTransformationChanged)
    {
        if (visible()) {
            // Update the node components
            updateComponents();

            // Update node
            internalUpdate();

            if (transformationNeedsUpdate()) {
                parentTransformationChanged = true;
            }

			if (parentTransformationChanged) {
				updateGlobalTransformation(m_parent ? m_parent->globalTransform() : Transform{});
			}

            for (auto&& renderizable : m_renderNodes.nodes) {
                renderizable->render();
            }

            for (auto&& group : m_groups.nodes) {
                group->render(parentTransformationChanged);
            }

            updateRemoves();
        }
    }

    const Rectf32 &SceneNode::scenePerspective()
    {
        return sceneManager().viewRect();
    }

    bool SceneNode::moveLastBeforeNode(const sptr<SceneNode> &beforeNode)
    {
        __ASSERT(!m_groups.nodes.empty(), "Cannot moveLastInsertedBeforeNode on empty container");
        if (!beforeNode) return false;

        // Find the node to swap before to
        auto iterator (std::find(m_groups.nodes.begin(), m_groups.nodes.end(),beforeNode));

        // If beforeNode not found, nothing to do
        if (iterator == m_groups.nodes.end()) return false;

        // If beforeNode is the last element, nothing to do
        if (iterator == std::prev(m_groups.nodes.end())) return false;

        auto last(std::prev(m_groups.nodes.end()));

        // Do not swap yourself
        if (*iterator == *last) return false;

        // Swap the iterators
        std::swap(*iterator, *last);
        return true;
    }

    void SceneNode::for_each_node(function<void(const sptr<Renderizable>&)> action) const
    {
        std::for_each(m_renderNodes.nodes.cbegin(), m_renderNodes.nodes.cend(), action);
    }

    void SceneNode::for_each_group(function<void(const sptr<SceneNode>&)> action) const
    {
        std::for_each(m_groups.nodes.cbegin(), m_groups.nodes.cend(), action);
    }

    void SceneNode::addRenderizable(sptr<Renderizable> newElement)
    {
        m_renderNodes.nodes.push_back(std::move(newElement));
    }

    void SceneNode::addSceneNode(sptr<SceneNode> node)
    {
        m_groups.nodes.push_back(node);
        node->m_parent = this;
        node->onCreated();
    }

    void SceneNode::updateRemoves()
    {
        m_groups.deferred_remove();
        m_renderNodes.deferred_remove();
    }

    void SceneNode::removeSceneNode(sptr<SceneNode> element)
    {
        __ASSERT(this != element.get(), "Cannot delete myself from myself");
        m_groups.m_nodesToDelete.push_back(std::move(element));
    }

    void SceneNode::removeRenderizable(sptr<Renderizable> element)
    {
        m_renderNodes.m_nodesToDelete.push_back(std::move(element));
    }

    void SceneNode::clearAll()
    {
        clearNodes();
        clearComponents();
    }
    void SceneNode::clearRenderizables()
    {
        updateRemoves();
        m_renderNodes.nodes.clear();
    }

    void SceneNode::clearSceneNodes()
    {
        updateRemoves();
        m_groups.nodes.clear();
    }

    void SceneNode::clearNodes()
    {
        clearRenderizables();
        clearSceneNodes();
    }
}
