//
// Created by kgb on 29.01.2021.
//

#ifndef FRACTAL_RENDERER_DIRECTIONALLIGHTCOMPONENT_H
#define FRACTAL_RENDERER_DIRECTIONALLIGHTCOMPONENT_H

#include "LightComponent.h"
#include <glm/glm.hpp>
using namespace glm;

class DirectionalLightComponent : public LightComponent {
public:
    vec3 direction;
    DirectionalLightComponent(vec3 dir, vec3 col): direction(dir), LightComponent(col){};
};


#endif //FRACTAL_RENDERER_DIRECTIONALLIGHTCOMPONENT_H
