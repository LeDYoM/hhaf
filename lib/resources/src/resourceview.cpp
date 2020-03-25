#include "resourceview.hpp"

#include <lib/include/liblog.hpp>
#include <lib/system/i_include/get_system.hpp>
#include <lib/resources/i_include/resourcemanager.hpp>

namespace lib::scene
{
void ResourceView::onAttached()
{
    retriever_ = &(sys::getSystem<sys::ResourceManager>(attachedNode()));
    log_assert(retriever_ != nullptr, "Invalid IResourceRetrieved");
}

mtps::sptr<scene::ITTFont> ResourceView::getTTFont(const mtps::str&rid)
{
    return retriever_->getTTFont(rid);
}

mtps::sptr<scene::ITexture> ResourceView::getTexture(const mtps::str&rid)
{
    return retriever_->getTexture(rid);
}

mtps::sptr<scene::IShader> ResourceView::getShader(const mtps::str&rid)
{
    return retriever_->getShader(rid);
}

mtps::sptr<scene::IFont> ResourceView::getBMPFont(const mtps::str&rid)
{
    return retriever_->getBMPFont(rid);
}

} // namespace lib::scene
