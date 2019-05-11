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
	};

	Renderizables::Renderizables()
		: priv_{ muptr<RenderizablesPrivate>() } {}

    Renderizables::~Renderizables() = default;

	void Renderizables::update()
	{
	}
}
