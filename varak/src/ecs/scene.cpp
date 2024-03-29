#include "varak/ecs/scene.h"
#include "varak/ecs/entity.h"
#include "varak/renderer/renderer2d.h"

namespace Varak {

    Scene::Scene(uint32_t viewportWidth, uint32_t viewportHeight)
        : m_viewportWidth(viewportWidth), m_viewportHeight(viewportHeight)
    {
        m_registry.on_construct<CameraComponent>().connect<&Scene::onCameraComponentAdded>(this);
    }

    Scene::~Scene() {}

    void Scene::onUpdate(Timestep ts) {}

    void Scene::onRenderEditor(EditorCamera& camera)
    {
        auto group = m_registry.group<TransformComponent, SpriteRendererComponent>();

        Renderer2D::beginScene(camera.getViewProjection());

        for (auto entity : group)
        {
            auto [transformComponent, spriteComponent] =
                group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::drawRect(transformComponent.getMatrix(), spriteComponent.color);
        }

        Renderer2D::endScene();
    }

    void Scene::onPlayRuntime()
    {
        VR_CORE_INFO("played"); //
    }

    void Scene::onStopRuntime()
    {
        VR_CORE_INFO("stoped"); //
    }

    void Scene::onRenderRuntime()
    {
        CameraComponent* mainCamera = nullptr;
        glm::mat4 cameraTransform;
        {
            auto view = m_registry.view<TransformComponent, CameraComponent>();

            for (auto entity : view)
            {
                auto [transformComponent, cameraComponent] =
                    view.get<TransformComponent, CameraComponent>(entity);

                if (cameraComponent.primary)
                {
                    mainCamera = &cameraComponent;
                    cameraTransform = transformComponent.getMatrix();
                    break;
                }
            }
        }

        if (mainCamera)
        {
            auto group = m_registry.group<TransformComponent, SpriteRendererComponent>();

            glm::mat4 viewMatrix = glm::inverse(cameraTransform);
            Renderer2D::beginScene(mainCamera->getProjection() * viewMatrix);

            for (auto entity : group)
            {
                auto [transformComponent, spriteComponent] =
                    group.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::drawRect(transformComponent.getMatrix(), spriteComponent.color);
            }

            Renderer2D::endScene();
        }
    }

    void Scene::onViewportResize(uint32_t width, uint32_t height)
    {
        m_viewportWidth = width;
        m_viewportHeight = height;

        // resize all non fixed aspect ratio
        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.fixedAspectRatio)
                cameraComponent.setViewportSize(width, height);
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

    void Scene::onCameraComponentAdded(entt::registry& /*registry*/, entt::entity entity)
    {
        m_registry.get<CameraComponent>(entity).setViewportSize(m_viewportWidth, m_viewportHeight);
    }

} // namespace Varak
