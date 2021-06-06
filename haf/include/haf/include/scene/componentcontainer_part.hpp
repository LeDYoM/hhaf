#ifndef HAF_SCENE_COMPONENTCONTAINERPART_INCLUDE_HPP
#define HAF_SCENE_COMPONENTCONTAINERPART_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#include <haf/include/scene/icomponent.hpp>
#include <haf/include/utils/attachable_manager.hpp>
#include <htypes/include/lockablevector.hpp>
#include <htypes/include/types.hpp>
#include <typeindex>

namespace haf::scene
{
/**
 * @brief Templated class representing a templated part of a component
 * container.
 * A component container part contains methods to manage the components
 * added to it.
 *
 * @tparam WithUpdate Specify if the components to add in this component
 * container should contain update function or not and if this function will
 * be updated.
 */
template <bool WithUpdate>
class ComponentContainerPart
    : public utils::AttachableManager<IComponentBase<WithUpdate>>
{
public:
    using ComponentType  = IComponentBase<WithUpdate>;
    using BaseClass      = utils::AttachableManager<ComponentType>;
    using AttachableType = typename BaseClass::AttachableType;

    using BaseClass::AttachableManager;

    template <typename T>
    htps::sptr<T> addComponentOfType()
    {
        LogAsserter::log_assert(componentOfType<T>() == nullptr,
                                "There is already a component with this type");
        htps::sptr<T> nc(BaseClass::template create<T>());
        addComponent(nc);
        return nc;
    }

    template <typename T>
    void ensureComponentOfType(htps::sptr<T>& element)
    {
        if (!element)
        {
            element = addComponentOfType<T>();
        }
    }

    void updateComponents()
    {
        if constexpr (WithUpdate)
        {
            components_.performUpdate(
                [](const htps::sptr<IComponent>& component) {
                    component->update();
                });
        }
        else
        {
            components_.update();
        }
    }

    /**
     * Returns the component of the specified type if exists
     * @tparam T type of the component to be retrieved
     * @return A shared pointer to the container or nullptr if not found
     */
    template <typename T>
    htps::sptr<T> componentOfType() const
    {
        htps::sptr<ComponentType> cot(
            componentOfType(std::type_index(typeid(T))));
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    void clearComponents() noexcept { components_.clear(); }

private:
    bool addComponent(htps::sptr<ComponentType> nc)
    {
        LogAsserter::log_assert(nc != nullptr,
                                "Trying to add a nullptr component");
        components_.emplace_back(std::move(nc));
        return true;
    }

    template <typename T>
    void addComponentOfType(htps::sptr<T>& component)
    {
        component = addComponentOfType<T>();
    }

    std::type_index tindexOf(const htps::sptr<ComponentType>& c) const
    {
        return std::type_index(typeid(*c));
    }

    htps::sptr<ComponentType> getComponentFromTypeIndex(
        const std::type_index& tindex) const
    {
        const auto v{components_.next()};
        auto iterator(std::find_if(
            v.cbegin(), v.cend(),
            [this, &tindex](const htps::sptr<ComponentType>& component) {
                return tindexOf(component) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    const htps::sptr<ComponentType> componentOfType(
        const std::type_index& ti) const
    {
        return getComponentFromTypeIndex(ti);
    }

    htps::LockableVector<htps::sptr<ComponentType>> components_;
};

}  // namespace haf::scene

#endif
