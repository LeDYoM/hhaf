#include "resourceviewcomponent.hpp"

#include <lib/scene/scenenode.hpp>
#include <logger/include/log.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene
{
    void ResourceView::onAttached()
    {
    }

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
