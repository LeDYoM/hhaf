#include "datawrappercreator.hpp"

namespace lib::scene
{
DataWrapperCreator::~DataWrapperCreator() = default;

void DataWrapperCreator::initialize(rptr<IDataWrapper> dw)
{
    dw->attachedNode_ = scene_node_;
    dw->onAttached();
}
} // namespace lib::scene
