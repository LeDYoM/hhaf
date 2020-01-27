#include "scene.hpp"

namespace lib::scene
{
Scene::Scene(str name) : SceneNode{nullptr, std::move(name)}
{
    parent_scene_ = this;
}

Scene::~Scene() = default;
} // namespace lib::scene
