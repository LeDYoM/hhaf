#include "zoper_base_scene.hpp"

namespace zoper
{
using namespace haf;

ZoperBaseScene::ZoperBaseScene(mtps::str scene_name) :
    BaseClass{std::move(scene_name)}
{}

ZoperBaseScene::~ZoperBaseScene() = default;

void ZoperBaseScene::onCreated()
{
    BaseClass::onCreated();
}

}  // namespace zoper
