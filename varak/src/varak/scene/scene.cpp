#include "varak/scene/scene.h"

#include "varak/scene/components.h"
#include "varak/scene/entity.h"

#include "varak/renderer/renderer2d.h"

namespace Varak {

    Scene::Scene(uint32_t width, uint32_t height)
        : m_viewportWidth(width), m_viewportHeight(height)
    {
    }

    Scene::~Scene() {}

    void Scene::onUpdate(Timestep ts)
    {

        auto group = m_registry.group<TransformComponent>(
            entt::get<SpriteRendererComponent>);

        for (auto entity : group)
        {
            auto [transform, sprite] =
                group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::drawRect(transform.transform, sprite.color);
        }
    }

    Entity Scene::createEntity()
    {
        Entity entity(m_registry.create(), this);
        entity.addComponent<TransformComponent>();
        return entity;
    }

    void Scene::destroyEntity(Entity& entity)
    {
        m_registry.destroy(entity); //
    }

} // namespace Varak
