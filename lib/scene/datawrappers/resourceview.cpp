#include "resourceview.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene
{
    ResourceView::~ResourceView() = default;
    
    sptr<scene::ITTFont> ResourceView::getFont(const str &rid)
    {
        return attachedNode()->parentScene()->sceneManager().resources().getFont(rid);
    }

    sptr<scene::ITexture> ResourceView::getTexture(const str &rid)
    {
        return attachedNode()->parentScene()->sceneManager().resources().getTexture(rid);
    }

    sptr<scene::IShader> ResourceView::getShader(const str &rid)
    {
        return attachedNode()->parentScene()->sceneManager().resources().getShader(rid);
    }
}
