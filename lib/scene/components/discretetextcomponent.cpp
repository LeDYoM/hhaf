#include "discretetextcomponent.hpp"

namespace lib::scene
{
	void DiscreteTextComponent::incrementIndex() noexcept
	{
		if (index() < (data().size() - 1)) {
			index = index() + 1;
		}
		else {
			if (circleAroud()) {
				index = 0;
			}
		}
	}

	void DiscreteTextComponent::decrementIndex() noexcept
	{
		_setText(data()[index()]);

		if (index() > 0) {
			index = index() - 1;
		}
		else {
			if (circleAroud()) {
				index = (data().size() - 1);
			}
		}
	}

	void DiscreteTextComponent::update()
	{
		if (index.hasChanged()) {
			_setText(data()[index()]);
		}
	}

	void DiscreteTextComponent::_setText(const str & nText)
	{
		node()->text.set(nText);
	}
}