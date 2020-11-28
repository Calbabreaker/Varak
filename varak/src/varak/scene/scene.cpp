#include "vrpch.h"

#include "varak/scene/scene.h"

#include "varak/scene/components.h"
#include "varak/scene/entity.h"

#include "varak/renderer/renderer2d.h"

namespace Varak {

    Scene::Scene(uint32_t viewportWidth, uint32_t viewportHeight)
        : m_viewportWidth(viewportWidth), m_viewportHeight(viewportHeight)
    {
    }

    Scene::~Scene() {}

    void Scene::onUpdate(Timestep ts)
    {
        // render 2d

        // TODO: this should not be a loop but a pointer
        Camera* mainCamera = nullptr;
        glm::mat4 cameraTransform;
        {
            auto view = m_registry.view<TransformComponent, CameraComponent>();

            for (auto entity : view)
            {
                auto [transformComponent, cameraComponent] = view.get<TransformComponent, CameraComponent>(entity);

                if (cameraComponent.primary)
                {
                    mainCamera = &cameraComponent.camera;
                    cameraTransform = transformComponent.transform;
                    break;
                }
            }
        }

        if (mainCamera)
        {
            auto group = m_registry.group<TransformComponent, SpriteRendererComponent>();

            Renderer2D::beginScene(*mainCamera, cameraTransform);

            for (auto entity : group)
            {
                auto [transformComponent, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::drawRect(transformComponent.transform, sprite.color);
            }

            Renderer2D::endScene();
        }
    }

    void Scene::onViewportResize(uint32_t width, uint32_t height)
    {
        m_viewportWidth = width;
        m_viewportHeight = m_viewportHeight;

        // resize all non fixed aspect ratio
        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.fixedAspectRatio)
            {
                cameraComponent.camera.setViewportSize(width, height);
            }
        }
    }

    Entity Scene::createEntity(const std::string& name)
    {
        Entity entity(m_registry.create(), this);
        entity.addComponent<IdentifierComponent>(name);
        entity.addComponent<TransformComponent>();
        return entity;
    }

    void Scene::destroyEntity(Entity entity)
    {
        m_registry.destroy(entity); //
    }

    template <typename T>
    void Scene::onComponentAdded(Entity entity, T& component)
    {
        static_assert(false);
    }

    template <>
    void Scene::onComponentAdded<IdentifierComponent>(Entity entity, IdentifierComponent& component)
    {
    }

    template <>
    void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {
    }

    template <>
    void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        component.camera.setViewportSize(m_viewportWidth, m_viewportHeight);
    }

    template <>
    void Scene::onComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
    }

} // namespace Varak
