HTPS_PRAGMA_ONCE
#ifndef HAF_RENDERIZABLES_COMPONENT_INCLUDE_HPP
#define HAF_RENDERIZABLES_COMPONENT_INCLUDE_HPP

#include <haf/include/core/types.hpp>

#include <haf/include/haf_export.hpp>
#include <haf/include/render/renderizables.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/component/component_order.hpp>

namespace haf::scene
{
class HAF_API RenderizableGroupComponent : public component::Component
{
public:
    static constexpr auto StaticTypeName{"RenderizableGroupComponent"};
    static constexpr component::ComponentOrder::Value StaticComponentOrder{0U};

    void onAttached() override;

    void update() override;

    auto renderizablesCount() const noexcept { return renderizables_.size(); }

    bool emptyRenderizables() const noexcept { return renderizables_.empty(); }

    decltype(auto) operator[](core::size_type const index) const noexcept
    {
        return renderizables_[index];
    }

    auto renderizableBuilder()
    {
        return renderizables_.renderizableBuilder();
    }

    core::sptr<render::Renderizable> const& first() const noexcept;

    core::str staticTypeName() const noexcept override;
    component::ComponentOrder::Value componentOrder() const noexcept override;

private:
    render::Renderizables renderizables_;
};

}  // namespace haf::scene

#endif
