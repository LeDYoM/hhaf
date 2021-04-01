#ifndef HAF_SCENE_TEXT_TABLENODE_INCLUDE_HPP
#define HAF_SCENE_TEXT_TABLENODE_INCLUDE_HPP

#include <haf/scene_nodes/include/tablenode.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>
#include <haf/scene_nodes/include/scenenodetext_properties.hpp>

namespace haf::scene::nodes
{
class TextTableNode : public TableNode<SceneNodeText>
{
    using BaseClass = TableNode<SceneNodeText>;

public:
    using BaseClass::BaseClass;
    using BaseClass::prop;

    template <typename PropertyType>
    void setProperty(PropertyType::value_type value)
    {
        for_each_tableSceneNode([&value](auto const&, htps::sptr<SceneNodeText> const& node)
        {
            node->template prop<PropertyType>().set(value);
        });
    }
};
}  // namespace haf::scene::nodes

#endif
