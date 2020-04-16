#include "resourceview.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/system/i_include/get_system.hpp>
#include <haf/resources/i_include/resourcemanager.hpp>

using namespace mtps;

namespace haf::scene
{
void ResourceView::onAttached()
{
    retriever_ = &(sys::getSystem<sys::ResourceManager>(attachedNode()));
    LogAsserter::log_assert(retriever_ != nullptr, "Invalid IResourceRetrieved");
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

} // namespace haf::scene
