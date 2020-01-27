#include "resourceview.hpp"

#include <lib/system/scenemanager.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/include/liblog.hpp>

namespace lib::scene
{
void ResourceView::onCreated()
{
    retriever_ = &(attachedNode()->sceneManager().resources());
    log_assert(retriever_ != nullptr, "Invalid IResourceRetrieved");
}

sptr<scene::ITTFont> ResourceView::getTTFont(const str &rid)
{
    return retriever_->getTTFont(rid);
}

sptr<scene::ITexture> ResourceView::getTexture(const str &rid)
{
    return retriever_->getTexture(rid);
}

sptr<scene::IShader> ResourceView::getShader(const str &rid)
{
    return retriever_->getShader(rid);
}

sptr<scene::IFont> ResourceView::getBMPFont(const str &rid)
{
    return retriever_->getBMPFont(rid);
}

} // namespace lib::scene
