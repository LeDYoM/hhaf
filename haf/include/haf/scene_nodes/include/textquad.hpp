#ifndef HAF_SCENE_TEXTQUAD_INCLUDE_HPP
#define HAF_SCENE_TEXTQUAD_INCLUDE_HPP

#include <haf/scene_nodes/include/tablenode.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>

namespace haf::scene::nodes
{
class TextQuad : public TableNode<SceneNodeText>
{
private:
    using BaseClass = TableNode<SceneNodeText>;
public:
    using BaseClass::BaseClass;
    using BaseClass::prop;

    ~TextQuad() override;

    void onCreated() override;

    void configure(htps::sptr<res::IFont> font,
                   const Color& color,
                   const htps::vector2df& size);

    inline htps::sptr<SceneNodeText> text(htps::vector2dst index) noexcept
    {
        return nodeAt(std::move(index));
    }
};
}  // namespace haf::scene::nodes

#endif
