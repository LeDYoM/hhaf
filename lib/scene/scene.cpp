#include "scene.hpp"

namespace lib::scene
{
Scene::Scene(str name) : SceneNode{nullptr, std::move(name)} {}

Scene::~Scene() = default;
} // namespace lib::scene
