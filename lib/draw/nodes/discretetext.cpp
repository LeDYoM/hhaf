#include "discretetext.hpp"

namespace lib
{
	namespace draw
	{
		namespace nodes
		{
			namespace
			{
				template <typename T, typename V>
				inline void _internalSetText(T *const t, const V&v, const u32 index)
				{
					t->text = v[index];
				}
			}
			void DiscreteText::configure()
			{
				configureBase();
				updateGeometry();
			}

			void DiscreteText::incrementIndex() noexcept
			{
				if (index() < (data().size()-1)) {
					index = index() + 1;
				}
				else {
					index = 0;
				}
			}

			void DiscreteText::decrementIndex() noexcept
			{
				if (index() > 0) {
					index = index() - 1;
				}
				else {
					index = (data().size() - 1);
				}
			}

			void DiscreteText::configureBase()
			{
				index.setCallback([this]()
				{
					if (index() < data().size()) {
						_internalSetText(this, data(), index());
					}
				});
				data.setCallback([this]()
				{
					if (data().empty()) {
						// Nothing to show
						text = "";
					}
					else if (index() >= data().size()) {
						index = (data().size() - 1);
					}
					else {
						index.update();
					}
				});
				data.update();
				NodeText::configureBase();
			}
		}
	}
}
