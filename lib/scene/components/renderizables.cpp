#include "renderizables.hpp"

#include <logger/include/log.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene
{

	class Renderizables::RenderizablesPrivate
	{
    public:
        RenderizablesPrivate() {}
        ~RenderizablesPrivate() {}

        vector<sptr<Renderizable>> render_nodes_;
	};

	Renderizables::Renderizables()
		: priv_{ muptr<RenderizablesPrivate>() } {}

    Renderizables::~Renderizables() = default;

	void Renderizables::update()
	{
	}

    void Renderizables::removeRenderizable(sptr<Renderizable> element)
    {
        assert_debug(element.get() != nullptr, "Received empty renderizable node to be deleted");

        priv_->render_nodes_.remove_value(element);
    }

    void Renderizables::clearRenderizables()
    {
        priv_->render_nodes_.clear();
    }

    void Renderizables::for_each_node(function<void(const sptr<Renderizable>&)> action) const
    {
        std::for_each(priv_->render_nodes_.cbegin(), priv_->render_nodes_.cend(), action);
    }

    void Renderizables::addRenderizable(sptr<Renderizable> newElement)
    {
        priv_->render_nodes_.push_back(std::move(newElement));
    }
}
