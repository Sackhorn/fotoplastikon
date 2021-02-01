//
// Created by kgb on 31.01.2021.
//

#ifndef FRACTAL_RENDERER_SPOTLIGHTCOMPONENT_H
#define FRACTAL_RENDERER_SPOTLIGHTCOMPONENT_H
#include "LightComponent.h"


class SpotLightComponent : public LightComponent
{
public:
    float spotlightAngle;
    vec3 direction;
    //we could deduce direction from Transform rotation and position
    SpotLightComponent(float angle, vec3 dir, vec3 col) : direction(dir), spotlightAngle(angle), LightComponent(col){};
};


#endif //FRACTAL_RENDERER_SPOTLIGHTCOMPONENT_H
