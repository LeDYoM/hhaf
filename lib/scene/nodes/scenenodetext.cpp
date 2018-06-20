#include "scenenodetext.hpp"

namespace lib::scene::nodes
{
    SceneNodeText::SceneNodeText(SceneNode * parent, str name)//, sptr<TTFont> font, const u32 characterSize, const Color &color, const Rectf32 & box)
        : SceneNode{ parent, std::move(name) }
    {
    }

    SceneNodeText::~SceneNodeText() = default;

    namespace
    {
    /*
        void updateTextLetters() {
            auto currentSize(sceneNodesSize());

            if (text().size() > currentSize) {

            }
        }
        */
    }
    void SceneNodeText::update()
    {
        BaseClass::update();

//        if (text.readResetHasChanged()) {
//
//        }
    }

}
