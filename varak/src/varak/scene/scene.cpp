#include "varak/scene/scene.h"

#include "varak/scene/components.h"
#include "varak/scene/entity.h"

#include "varak/renderer/renderer2d.h"

namespace Varak {

    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::onUpdate(Timestep ts)
    {
        // render
        auto group =
            m_registry.group<TransformComponent>(entt::get<SpriteComponent>);

        for (auto entity : group)
        {
            auto [transform, sprite] =
                group.get<TransformComponent, SpriteComponent>(entity);
            Renderer2D::drawRect(transform.transform, sprite.color);
        }
    }

    Entity Scene::createEntity()
    {
        Entity entity(m_registry.create(), this);
        entity.addComponent<TransformComponent>();
        return entity;
    }

    void Scene::destroyEntity(Entity& entity) { m_registry.destroy(entity); }

} // namespace Varak
