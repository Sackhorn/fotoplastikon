#define NOMINMAX

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

void foo()
{
    while(true)
    {
        auto* meshComponent = new Texture("../mesh/color.png");
        delete meshComponent;
    }
}

int main()
{
    entt::registry* mainRegistry = MainRegistry::GetMainRegistry();
    auto renderer = Renderer();

    auto camera = MainRegistry::createEntity();
    auto& cameraComponent = mainRegistry->emplace<CameraComponent>(camera);
    auto& cameraTransform = mainRegistry->get<TransformComponent>(camera);
    auto camera2 = MainRegistry::createEntity();
    auto& cameraComponent2 = mainRegistry->emplace<CameraComponent>(camera2);

    vector<vec3> meshesPositions = {
            vec3(0.0, 1.0, -3.0),
            vec3(0.0, -1.0, -3.0),
            vec3(-1.0, 0.0, -3.0),
            vec3(1.0, 0.0, -3.0),

            vec3(1.0, 1.0, -3.0),
            vec3(1.0, -1.0, -3.0),
            vec3(-1.0, 1.0, -3.0),
            vec3(-1.0, -1.0, -3.0),
            vec3(0.0, 0.0, -3.0),

    };
    srand(time(NULL));
    for(vec3 position: meshesPositions)
    {
        entt::entity mesh = MainRegistry::createEntity();
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
//    std::thread run(foo);
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
        renderer.Update();
    }
	return 0;
}

