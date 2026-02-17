module;

#include <haf/include/haf_export.hpp>

export module haf:components:component_container;

import :component_requirements;
import :ordered_component_group;
import :unordered_component_group;
import :core;
import :component;
import :utils:type_data;

namespace haf::component
{
struct ComponentContainer::ComponentContainerPrivate
{
    rptr<scene::SceneNode> const m_attachable;
    OrderedComponentGroup m_ordered_component_group;
    UnorderedComponentGroup m_unordered_component_group;

    explicit ComponentContainerPrivate(
        rptr<scene::SceneNode> attachable) noexcept :
        m_attachable{attachable}
    {}
};

/**
 * @brief class representing a container for components.
 * @see Component
 */
class HAF_API ComponentContainer
{
public:
    explicit ComponentContainer(core::rptr<class scene::SceneNode> attachable) :
        m_p{make_pimplp<ComponentContainerPrivate>(attachable)}
    {}

    /**
     * @brief Destroy the Component Container object
     */
    virtual ~ComponentContainer() = default;

    /**
     * @brief Create or get a pointer to a component type. This method
     * could create an instance of the component and add it to the component
     * list or retrieve a pointer to it
     *
     * @tparam T Type of the component
     * @return Pointer to the component type. Either newly created or already
     * existing
     */
    template <typename T>
    core::sptr<T> component()
    {
        core::sptr<T> result{componentOfType<T>()};
        if (result == nullptr)
        {
            result = core::msptr<T>();
            attachComponent(result);
        }
        return result;
    }

    /**
     * @brief Retrieve the attached instance of a component if it exists.
     *
     * @tparam T Type of the component
     * @return Pointer to the component or nullptr
     */
    template <typename T>
    core::sptr<T> componentOfType() const
    {
        auto cot{componentOfType(utils::type_of<T>())};
        return cot ? core::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    /**
     * @brief Retrieve the attached instance of a component if it exists.
     *
     * @tparam T Type of the component
     * @param element Pointer where the output wil be stored. It will be nullptr
     * if the component does not exist.
     */
    template <typename T>
    void componentOfType(core::sptr<T>& element) const
    {
        element = componentOfType<T>();
    }

    /**
     * @brief Retrieve an instance of a component type. Either newly created
     * or already existing
     *
     * @tparam T Type of the component
     * @param element Return value as a reference. Template deduction will
     * get the required type.
     */
    template <typename T>
    void component(core::sptr<T>& element)
    {
        if (element == nullptr)
        {
            element = component<T>();
        }
    }

    /**
     * @brief Update componentents of this container
     */
    void updateUnorderedComponents()
    {
        for (auto index{0U}; index < m_p->m_unordered_component_group.size();
             ++index)
        {
            if (auto&& component{m_p->m_unordered_component_group[index]};
                component != nullptr)
            {
                component->update();
            }
        }
    }

    void updateIndexedComponent(uint32_t const index)
    {
        if (index < m_p->m_ordered_component_group.size())
        {
            if (auto&& component{m_p->m_ordered_component_group[index]};
                component != nullptr)
            {
                component->update();
            }
        }
    }

    /**
     * @brief Clear all elements of this container
     */
    void clearComponents() noexcept
    {
        m_p->m_ordered_component_group.clear();
        m_p->m_unordered_component_group.clear();
    }

    core::size_type components() const noexcept
    {
        return m_p->m_ordered_component_group.size() +
            m_p->m_unordered_component_group.size();
    }

private:
    /**
     * @brief Add a new component to the corresponding list
     * @param newComponent Component to be added
     * @note This function does not check if the component is already added, so
     * it assumes it is not
     */
    void attachComponent(core::sptr<Component> newComponent)
    {
        applyRequirements(*newComponent);
        initialize(*newComponent);

        if (auto const order{newComponent->componentOrder()};
            order == ComponentOrder::NoOrder)
        {
            m_p->m_unordered_component_group.PushBack(htps::move(newComponent));
        }
        else
        {
            m_p->m_ordered_component_group.insertAtIndex(
                static_cast<u32>(order), htps::move(newComponent));
        }
    }

    void applyRequirements(Component& _thisComponent)
    {
        ComponentRequirements component_requierements{*this};
        _thisComponent.addRequirements(component_requierements);
    }

    core::rptr<class scene::SceneNode> attachable() const noexcept
    {
        return m_p->m_attachable;
    }

    void initialize(component::Component& component) const
    {
        component.setAttachedNode(attachable());
    }

    core::sptr<Component> componentOfType(utils::type_index const& ti) const
    {
        if (auto c{
                m_p->m_ordered_component_group.getComponentFromTypeIndex(ti)};
            c == nullptr)
        {
            return m_p->m_unordered_component_group.getComponentFromTypeIndex(
                ti);
        }
        else
        {
            return c;
        }
    }

    struct ComponentContainerPrivate;
    core::PImplPointer<ComponentContainerPrivate> m_p;

    friend class scene::SceneController;
};

}  // namespace haf::component
