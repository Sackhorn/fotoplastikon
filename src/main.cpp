
#if defined(_MSC_VER)
    #define HS(str) __pragma(warning(suppress:4307)) entt::hashed_string{str}
#else
    #define HS(str) entt::hashed_string{str}
#endif

#include <TransformComponent.h>
#include "MeshComponent.h"
#include "Renderer.h"
#include "RegistryHierarchy.h"
#include "CameraComponent.h"
#include <thread>

int main()
{
    entt::registry* mainRegistry = MainRegistry::GetMainRegistry();
    auto renderer = Renderer();
    auto camera = MainRegistry::CreateEntity();
    auto& cameraComponent = mainRegistry->emplace<CameraComponent>(camera);
    auto& cameraTransform = mainRegistry->get<TransformComponent>(camera);
    auto camera2 = MainRegistry::CreateEntity();
    auto& cameraComponent2 = mainRegistry->emplace<CameraComponent>(camera2);
    TransformComponent& camera2Transform = mainRegistry->get<TransformComponent>(camera2);
    camera2Transform._position.z -= 3.0f;
    camera2Transform.UpdateMatrices();
    auto dirLight = MainRegistry::CreateEntity();
//    auto& dirLightComponent = mainRegistry->emplace<DirectionalLightComponent>(dirLight, vec3(0.0, 0.0, 1.0), vec3(1.0));

//    auto pointLight = MainRegistry::CreateEntity();
//    auto& pointLightComponent = mainRegistry->emplace<PointLightComponent>(pointLight, vec3(1.0));
//    auto& pointLightTransform = mainRegistry->get<TransformComponent>(pointLight);
//    pointLightTransform._position = vec3(0.0, 0.0, -10.0f);
//    pointLightTransform.UpdateMatrices();
//
//    auto pointLight2 = MainRegistry::CreateEntity();
//    auto& pointLightComponent2 = mainRegistry->emplace<PointLightComponent>(pointLight2, vec3(1.0));
//    auto& pointLightTransform2 = mainRegistry->get<TransformComponent>(pointLight2);
//    pointLightTransform2._position = vec3(0.0, 0.0, -3.0f);
//    pointLightTransform2.UpdateMatrices();

    auto spotLight = MainRegistry::CreateEntity();
    auto& spotLightComponent = mainRegistry->emplace<SpotLightComponent>(
            spotLight,
            10.0f,
            vec3(0.0f, 0.0f, -1.0f),
            vec3(0.0f, 1.0f, 0.0f));
    mainRegistry->get<TransformComponent>(spotLight)._position = vec3(0.0f, 0.0f, 2.0f);
    mainRegistry->get<TransformComponent>(spotLight).UpdateMatrices();


//
    vector<vec3> meshesPositions = {
            vec3(0.0, 1.0, -3.0),
            vec3(0.0, -1.0, -3.0),
            vec3(-1.0, 0.0, -3.0),
            vec3(1.0, 0.0, -3.0),

            vec3(1.0, 1.0, -3.0),
            vec3(1.0, -1.0, -3.0),
            vec3(-1.0, 1.0, -3.0),
            vec3(-1.0, -1.0, -3.0),
            vec3(0.0, 0.0, -6.0),
            vec3(0.0, 1.0, -6.0),

    };
    srand(time(NULL));
    for(vec3 position: meshesPositions)
    {
        entt::entity mesh = MainRegistry::CreateEntity();
        MeshComponent &meshComponent = mainRegistry->emplace<MeshComponent>(mesh, "../mesh/sphere.obj");
        TransformComponent* meshTransform = &mainRegistry->get<TransformComponent>(mesh);
        meshTransform->_position = position;
        meshTransform->_scale = vec3(0.5);
        if(rand() % 2 == 0)
        {
            meshComponent.materialComponent->albedo = make_unique<Texture>("../mesh/color.png");
        }
        meshTransform->UpdateMatrices();
    }

    auto old = glfwGetTime();

    while(renderer.PollInput())
    {
        auto newTime = glfwGetTime();
        double dt = newTime - old;
        old = newTime;
        mainRegistry->view<TransformComponent, MeshComponent>().each([dt](auto entity, auto& transform, auto& mesh)
        {
            transform._rotation.y += dt * 1.0f;
            transform.UpdateMatrices();
        });
        mainRegistry->view<TransformComponent, CameraComponent>().each([dt](auto entity, auto& transform, auto& mesh){
            glm::vec3 rotAxis(0.0, 1.0, 0.0);
            float angle = glm::radians(60.0 * dt);
            vec3 rotateAroundPoint = vec3(0.0, 0.0, -3.0);
            mat4 tmp = glm::translate(transform.world, rotateAroundPoint);
            tmp = glm::rotate(tmp, angle, rotAxis);
            transform.world = glm::translate(tmp, -rotateAroundPoint);
        });
        renderer.Update();
    }
	return 0;
}

