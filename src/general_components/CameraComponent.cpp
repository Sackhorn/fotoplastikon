//
// Created by kgb on 18.07.2020.
//

#include "CameraComponent.h"
#include "RegistryHierarchy.h"


CameraComponent::CameraComponent()
{
    auto allCameras = MainRegistry::GetMainRegistry()->view<CameraComponent>();
    for(auto entity: allCameras)
    {
        auto& cameraComponent = MainRegistry::GetMainRegistry()->get<CameraComponent>(entity);
        cameraComponent.isActive = false;
    }
    this->isActive = true;
}
