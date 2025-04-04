HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENTS_TABLE_OF_INCLUDE_HPP
#define HAF_COMPONENTS_TABLE_OF_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/events/connection.hpp>
#include <haf/include/properties/properties.hpp>
#include <haf/include/scene_components/table.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::scene
{
/**
 * @brief Class representing a SceneNode with table layout.
 * Properties of the table can be configured like size and so on.
 * @tparam T
 */
template <typename T>
class HAF_API TableOf : public Table
{
    using BaseClass = Table;

public:
    using ContainedElement = T;

    using BaseClass::BaseClass;

    evt::emitter<fmath::vector2dst const, htps::sptr<T> const&>
        onTableNodeCreated;

    constexpr htps::sptr<T>& operator()(fmath::vector2dst const& index)
    {
        return nodeAt(index);
    }

    constexpr htps::sptr<T const> const operator()(
        fmath::vector2dst const& index) const noexcept
    {
        return nodeAt(index);
    }

    constexpr haf::scene::SceneNodeSPtr outerSceneNodeAt(
        fmath::vector2dst const& index) noexcept
    {
        return innerSceneNodeAt(index)->sceneNodes()[0];
    }

    constexpr haf::scene::SceneNodeSPtr const outerSceneNodeAt(
        fmath::vector2dst const& index) const noexcept
    {
        return innerSceneNodeAt(index)->sceneNodes()[0];
    }

    constexpr htps::sptr<T> nodeAt(fmath::vector2dst const& index) noexcept
    {
        return outerSceneNodeAt(index)->componentOfType<T>();
    }

    constexpr htps::sptr<T const> const nodeAt(
        fmath::vector2dst const& index) const noexcept
    {
        return outerSceneNodeAt(index)->componentOfType<T>();
    }

    constexpr void for_each_outerSceneNode(
        htps::function<void(fmath::vector2dst const& index,
                            htps::sptr<T> const&)> const action)
    {
        for_each_table_innerSceneNode(
            [action{htps::move(action)}](fmath::vector2dst const& index,
                                         htps::sptr<SceneNode>& node) {
                action(index, node->sceneNodes()[0]->componentOfType<T>());
            });
    }

    template <template <typename> typename PropertyType,
              typename PropertyValue,
              typename ObjectType>
    constexpr void set_property_for_each_table_node(
        PropertyType<PropertyValue>(ObjectType::* property_v),
        PropertyValue const& value)
    {
        for_each_outerSceneNode(
            [&value, property_v](fmath::vector2dst const&,
                                 htps::sptr<T> const& node) {
                set_property(node, property_v, value);
            });
    }

    constexpr void for_each_outerSceneNode_in_x(
        htps::size_type const x,
        htps::function<void(const htps::size_type, htps::sptr<T> const&)> const
            action)
    {
        for_each_outerSceneNode([&action, x](fmath::vector2dst const& pos,
                                             htps::sptr<T> const& node) {
            if (pos.x == x)
            {
                action(pos.y, node);
            }
        });
    }

    constexpr void for_each_outerSceneNode_in_y(
        htps::size_type const y,
        htps::function<void(htps::size_type const, htps::sptr<T> const&)> const
            action)
    {
        for_each_outerSceneNode([&action, y](fmath::vector2dst const& pos,
                                             htps::sptr<T> const& node) {
            if (pos.y == y)
            {
                action(pos.x, node);
            }
        });
    }

private:
    virtual void tableNodeCreated(fmath::vector2dst const&,
                                  htps::sptr<T> const&)
    {}

    void createNodeAt(fmath::vector2dst const& index) override final
    {
        auto createdNode{innerSceneNodeAt(index)};
        LogAsserter::log_assert(createdNode != nullptr,
                                "Error getting innerSceneNodeAt ", index);

        auto outerSceneNode{
            createdNode->createSceneNode(createdNode->name() + "__outer")};
        LogAsserter::log_assert(outerSceneNode != nullptr,
                                "Error creating outerSceneNode at ", index);

        LogAsserter::log_assert(outerSceneNode->componentOfType<T>() == nullptr,
                                "Cannot create component");
        outerSceneNode->component<T>();
        onTableNodeCreated(index, nodeAt(index));
        tableNodeCreated(index, nodeAt(index));
    }
};

}  // namespace haf::scene

#endif
