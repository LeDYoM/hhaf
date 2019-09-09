#include "resourceview.hpp"

#include <lib/scene/scenenode.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene
{
    ResourceView::~ResourceView() = default;
    
    sptr<scene::ITTFont> ResourceView::getTTFont(const str &rid)
    {
        return attachedNode()->sceneManager().resources().getTTFont(rid);
    }

    sptr<scene::ITexture> ResourceView::getTexture(const str &rid)
    {
        return attachedNode()->sceneManager().resources().getTexture(rid);
    }

    sptr<scene::IShader> ResourceView::getShader(const str &rid)
    {
        return attachedNode()->sceneManager().resources().getShader(rid);
    }

    sptr<scene::IFont> ResourceView::getBMPFont(const str &rid)
    {
        return attachedNode()->sceneManager().resources().getBMPFont(rid);
    }

}
