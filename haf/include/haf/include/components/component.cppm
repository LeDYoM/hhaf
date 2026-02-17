export module haf:components:component;

import :component_order;
import :core:types;
import :system_subsystem_view;
import :scenes:scene_node;
import :scenes:iscene_render_context_provider;

namespace haf::scene
{
class SceneNode;
class SceneController;
struct SceneRenderContext;
}  // namespace haf::scene

namespace haf::component
{
class ComponentRequirements;

class Component
{
public:
    using pointer       = htps::rptr<scene::SceneNode>;
    using const_pointer = htps::rptr<scene::SceneNode const>;

    /**
     * @brief Interface to be implemented to update the component
     */
    virtual void update() {}

    /**
     * @brief Destroy the Attachable object
     */
    virtual ~Component() = default;

    Component(Component const&)            = delete;
    Component& operator=(Component const&) = delete;
    Component(Component&&)                 = default;
    Component& operator=(Component&&)      = default;

    /**
     * @brief Method called after the component is attached to a node.
     * Override it to perform initialization
     */
    virtual void onAttached() {}

    /**
     * @brief Get the attached node.
     * @return The pointer to const attached node.
     */
    constexpr const pointer attachedNode() const noexcept
    {
        return m_attachedNode;
    }

    /**
     * @brief Get the attached node.
     * @return The pointer to the attached node.
     */
    constexpr pointer attachedNode() noexcept { return m_attachedNode; }

    /**
     * @brief This function is intended to be override.
     * @return ComponentOrder The expected order for this component
     */
    virtual ComponentOrder::Value componentOrder() const noexcept
    {
        return ComponentOrder::NoOrder;
    }

    virtual core::str staticTypeName() const noexcept { return "Component"; }

protected:
    Component() noexcept = default;

    scene::SceneRenderContext& sceneRenderContext()
    {
        return attachedNode()
            ->subSystem<scene::ISceneRenderContextProvider>()
            ->sceneRenderContext();
    }

    scene::SceneRenderContext const& sceneRenderContext() const
    {
        return attachedNode()
            ->subSystem<scene::ISceneRenderContextProvider>()
            ->sceneRenderContext();
    }

private:
    void setAttachedNode(pointer const attachedNode) noexcept
    {
        m_attachedNode = attachedNode;
        onAttached();
    }

    virtual void addRequirements(ComponentRequirements&) {}

    pointer m_attachedNode{nullptr};
    friend class ComponentContainer;
    friend class scene::SceneController;
};

}  // namespace haf::component
