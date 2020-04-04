#include "resourceview.hpp"

#include <lib/include/liblog.hpp>
#include <lib/system/i_include/get_system.hpp>
#include <lib/resources/i_include/resourcemanager.hpp>

using namespace mtps;

namespace lib::scene
{
void ResourceView::onAttached()
{
    retriever_ = &(sys::getSystem<sys::ResourceManager>(attachedNode()));
    log_assert(retriever_ != nullptr, "Invalid IResourceRetrieved");
}

sptr<scene::ITTFont> ResourceView::getTTFont(const str&rid)
{
    return retriever_->getTTFont(rid);
}

sptr<scene::ITexture> ResourceView::getTexture(const str&rid)
{
    return retriever_->getTexture(rid);
}

sptr<scene::IShader> ResourceView::getShader(const str&rid)
{
    return retriever_->getShader(rid);
}

sptr<scene::IFont> ResourceView::getBMPFont(const str&rid)
{
    return retriever_->getBMPFont(rid);
}

} // namespace lib::scene
