#ifndef HAF_SCENE_COMPONENTCONTAINERPART_INCLUDE_HPP
#define HAF_SCENE_COMPONENTCONTAINERPART_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#include <haf/scene/include/icomponent.hpp>
#include <haf/utils/include/attachable_manager.hpp>
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
    mtps::sptr<T> addComponentOfType()
    {
        LogAsserter::log_assert(componentOfType<T>() == nullptr,
                                "There is already a component with this type");
        mtps::sptr<T> nc(BaseClass::template create<T>());
        addComponent(nc);
        return nc;
    }

    template <typename T>
    void ensureComponentOfType(mtps::sptr<T>& element)
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
                [](const mtps::sptr<IComponent>& component) {
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
    mtps::sptr<T> componentOfType() const
    {
        mtps::sptr<ComponentType> cot(
            componentOfType(std::type_index(typeid(T))));
        return cot ? std::dynamic_pointer_cast<T>(cot) : nullptr;
    }

    void clearComponents() noexcept { components_.clear(); }

private:
    bool addComponent(mtps::sptr<ComponentType> nc)
    {
        LogAsserter::log_assert(nc != nullptr,
                                "Trying to add a nullptr component");
        components_.emplace_back(std::move(nc));
        return true;
    }

    template <typename T>
    void addComponentOfType(mtps::sptr<T>& component)
    {
        component = addComponentOfType<T>();
    }

    std::type_index tindexOf(const mtps::sptr<ComponentType>& c) const
    {
        return std::type_index(typeid(*c));
    }

    mtps::sptr<ComponentType> getComponentFromTypeIndex(
        const std::type_index& tindex) const
    {
        const auto v{components_.next()};
        auto iterator(std::find_if(
            v.cbegin(), v.cend(),
            [this, &tindex](const mtps::sptr<ComponentType>& component) {
                return tindexOf(component) == tindex;
            }));
        return (iterator == v.cend()) ? nullptr : (*iterator);
    }

    const mtps::sptr<ComponentType> componentOfType(
        const std::type_index& ti) const
    {
        return getComponentFromTypeIndex(ti);
    }

    mtps::LockableVector<mtps::sptr<ComponentType>> components_;
};

}  // namespace haf::scene

#endif
