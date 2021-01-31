//
// Created by kgb on 29.01.2021.
//

#ifndef FRACTAL_RENDERER_LIGHTCOMPONENT_H
#define FRACTAL_RENDERER_LIGHTCOMPONENT_H

#include "glm/glm.hpp"
using namespace glm;
class LightComponent {
public:
    vec3 color;
    LightComponent(vec3 c) : color(c) {};
};


#endif //FRACTAL_RENDERER_LIGHTCOMPONENT_H
