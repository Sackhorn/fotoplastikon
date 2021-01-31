//
// Created by kgb on 30.01.2021.
//

#ifndef FRACTAL_RENDERER_POINTLIGHTCOMPONENT_H
#define FRACTAL_RENDERER_POINTLIGHTCOMPONENT_H
#include "LightComponent.h"
#include <glm/glm.hpp>

class PointLightComponent : public LightComponent
{
public:
    float constantTerm, linearTerm, quadraticTerm;
    PointLightComponent(glm::vec3 col) : LightComponent(col),
                                        constantTerm(1.0f),
                                        linearTerm(0.09f),
                                        quadraticTerm(0.032f){};

};

#endif //FRACTAL_RENDERER_POINTLIGHTCOMPONENT_H
