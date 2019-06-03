#include "datawrappercreator.hpp"

namespace lib::scene
{
    DataWrapperCreator::~DataWrapperCreator() = default;

    void DataWrapperCreator::initialize(IDataWrapper *const dw)
    {
        dw->scene_node_ = scene_node_;
        dw->onCreated();
    }
}
