#include "renderizables.hpp"

#include <lib/include/core/log.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/scenemanager.hpp>

namespace lib::scene
{

	class Renderizables::RenderizablesPrivate
	{
    public:
        RenderizablesPrivate() {}
        ~RenderizablesPrivate() {}
	};

	Renderizables::Renderizables()
		: priv_{ muptr<RenderizablesPrivate>() } {}

    Renderizables::~Renderizables() = default;

	void Renderizables::update()
	{
	}
}
