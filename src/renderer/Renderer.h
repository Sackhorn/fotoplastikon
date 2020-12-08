//
// Created by kgb on 18.07.2020.
//

#ifndef FRACTAL_RENDERER_RENDERER_H
#define FRACTAL_RENDERER_RENDERER_H


#include "GL/gl3w.h"
#include <GLFW/glfw3.h>
#include "entt/entt.hpp"
#include "MeshComponent.h"
#include "TransformComponent.h"

class Renderer {

private:
    GLFWwindow* window;
    mat4 projection = glm::perspective(radians(45.0f), 1600.0f/900.0f, 0.1f, 100.0f);
public:
    Renderer() {CreateWindowContext(1600, 900);};
    ~Renderer();
    void CreateWindowContext(int width, int height);
    void Update();
    bool PollInput();
    static void SubmitMeshComponent(MeshComponent *meshComponent, TransformComponent *transformComponent, mat4 view, mat4 projection);
    mat4 GetViewMatrix();
};


#endif //FRACTAL_RENDERER_RENDERER_H
