//
// Created by kgb on 18.07.2020.
//

#ifndef FRACTAL_RENDERER_TRANSFORMCOMPONENT_H
#define FRACTAL_RENDERER_TRANSFORMCOMPONENT_H



#include <vector>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
using namespace std;
using namespace glm;

class TransformComponent
{

public:
    vec3 _position, _scale, _rotation;
    mat4 world;
    TransformComponent(vec3 position, vec3 scaleArg, vec3 rotation);
    TransformComponent();
//    TransformComponent(TransformComponent&);
//    TransformComponent(TransformComponent&&);
    void UpdateMatrices();
    static mat4 getWorldMatrix(const TransformComponent& transform);



};

#endif //FRACTAL_RENDERER_TRANSFORMCOMPONENT_H