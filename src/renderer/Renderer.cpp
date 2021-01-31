//
// Created by kgb on 18.07.2020.
//
#include "Renderer.h"
#include "CameraComponent.h"
#include <entt/entt.hpp>
#include "RegistryHierarchy.h"
#include "LoadShader.h"



void Renderer::CreateWindowContext(int width, int height){
        if( !glfwInit() )
        {

            fprintf( stderr, "Failed to initialize GLFW\n" );
            getchar();
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Open a window and create its OpenGL context
        window = glfwCreateWindow( width, height, "OpenGL", NULL, NULL);
        if( window == NULL )
        {
            fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
            getchar();
            glfwTerminate();
            throw std::runtime_error("GLFW failed to initialize");
        }
        glfwMakeContextCurrent(window);

        if (gl3wInit()) {
            fprintf(stderr, "Failed to initialize gl3w\n");
            throw std::runtime_error("GL3W failed to initialize");
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
    glfwTerminate();
}

void Renderer::Update()
{

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 view = GetViewMatrix();
    MainRegistry::GetMainRegistry()->view<MeshComponent, TransformComponent>().each(
            [view, this](auto entity, auto& mesh, auto& transform)
            {
                SubmitMeshComponent(&mesh, &transform, view, projection);
            });

    glfwSwapBuffers(window);
    glfwPollEvents();
}

mat4 Renderer::GetViewMatrix()
{
    mat4 view = mat4(1.0);
    view = translate(view, -vec3(0.0, 0.0, 1.0));

    TransformComponent* cameraTransform = nullptr;
    entt::registry * _mainRegistry = MainRegistry::GetMainRegistry();
    _mainRegistry->view<CameraComponent, TransformComponent>().each(
[&cameraTransform](auto entity, auto& camera, auto& transform)
    {
        if(camera.isActive)
            cameraTransform = &transform;
    });

    return cameraTransform->world;
}

bool Renderer::PollInput()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}

void Renderer::PassDirLightsToShader(GLShader* shader)
{
    auto view = MainRegistry::GetMainRegistry()->view<DirectionalLightComponent>();
    for(auto entity : view)
    {
        shader->SetDirectionalLight(view.get<DirectionalLightComponent>(entity));
    }
}

void Renderer::PassPointLightsToShader(GLShader* shader)
{
    auto view = MainRegistry::GetMainRegistry()->view<PointLightComponent, TransformComponent>();
    int i = 0;
    for(auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);
        auto& pointLight = view.get<PointLightComponent>(entity);
        shader->SetPointLight(pointLight, transform, i);
        i++;
    }
    shader->SetInt(i, "pointLightsNmbr");
}

void Renderer::SubmitMeshComponent(MeshComponent *meshComponent, TransformComponent *transformComponent, mat4 view, mat4 projection)
{
    auto wvp = projection * view * transformComponent->world;
    GLShader* shader = meshComponent->materialComponent->shader.get();
    unsigned int shaderID = shader->shaderID;
    unsigned int textureID = meshComponent->materialComponent->albedo->textureID;
    glUseProgram(shaderID);
    glBindVertexArray(*(meshComponent->VAO));
    PassDirLightsToShader(shader);
    PassPointLightsToShader(shader);
    shader->SetMat4(wvp, "wvp");
    shader->SetMat4(transformComponent->world, "world");
    shader->SetMat4(view, "view");
    shader->SetMat4(projection, "projection");
    shader->SetVec3(view[3], "viewPos");
    shader->SetTex(textureID, "albedo");
    shader->SetMaterialStruct(meshComponent->materialComponent->material);
    glDrawElements(GL_TRIANGLES, meshComponent->indices.size(), GL_UNSIGNED_INT, 0);
}
