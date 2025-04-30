HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLES_COMPONENT_INCLUDE_HPP
#define HAF_RENDERIZABLES_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/component/component.hpp>

namespace haf::scene
{
class HAF_API RenderizableGroupComponent : public component::Component
{
    using BaseClass = component::Component;

public:
    void onAttached() override;

    void update() override;

    auto renderizablesCount() const noexcept { return renderizables_.size(); }

    bool emptyRenderizables() const noexcept { return renderizables_.empty(); }

    decltype(auto) operator[](htps::size_type const index) const noexcept
    {
        return renderizables_[index];
    }

    auto renderizableBuilder() { return renderizables_.renderizableBuilder(); }

    htps::sptr<render::Renderizable> const& first() const noexcept;

private:
    render::Renderizables renderizables_;
};

}  // namespace haf::scene

#endif
